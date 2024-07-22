#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <openssl/sha.h>
#include <sys/stat.h>

/* Block structure */
typedef struct Block
{
	int index;
	char previous_hash[SHA256_DIGEST_LENGTH * 2 + 1];
	char timestamp[20];
	char data[256];
	char hash[SHA256_DIGEST_LENGTH * 2 + 1];
	struct Block *next;
} Block;

/* Blockchain structure */
typedef struct Blockchain
{
	Block *head;
} Blockchain;

Block *create_genesis_block()
{
	Block *genesis_block = (Block *)malloc(sizeof(Block));

	genesis_block->index = 0;
	strcpy(genesis_block->previous_hash, "0");
	time_t now = time(NULL);

	strftime(genesis_block->timestamp, sizeof(genesis_block->timestamp), "%Y-%m-%d %H:%M:%S", localtime(&now));
	strcpy(genesis_block->data, "Genesis Block");
	/* Compute hash */
	char temp[1024];

	snprintf(temp, sizeof(temp), "%d%s%s%s", genesis_block->index, genesis_block->previous_hash, genesis_block->timestamp, genesis_block->data);
	unsigned char hash[SHA256_DIGEST_LENGTH];

	SHA256((unsigned char *)temp, strlen(temp), hash);
	for (int i = 0; i < SHA256_DIGEST_LENGTH; ++i)
		sprintf(genesis_block->hash + (i * 2), "%02x", hash[i]);

	genesis_block->next = NULL;
	return (genesis_block);
}

Block *add_block(Block *previous_block, const char *data)
{
	Block *new_block = (Block *)malloc(sizeof(Block));

	new_block->index = previous_block->index + 1;
	strcpy(new_block->previous_hash, previous_block->hash);
	time_t now = time(NULL);
	strftime(new_block->timestamp, sizeof(new_block->timestamp), "%Y-%m-%d %H:%M:%S", localtime(&now));
	strcpy(new_block->data, data);
	/* Compute hash */
	char temp[1024];

	snprintf(temp, sizeof(temp), "%d%s%s%s", new_block->index, new_block->previous_hash, new_block->timestamp, new_block->data);
	unsigned char hash[SHA256_DIGEST_LENGTH];

	SHA256((unsigned char *)temp, strlen(temp), hash);
	for (int i = 0; i < SHA256_DIGEST_LENGTH; ++i)
		sprintf(new_block->hash + (i * 2), "%02x", hash[i]);
	new_block->next = NULL;
	previous_block->next = new_block;
	return (new_block);
}

void get_file_metadata(const char *filename, char *metadata)
{
	FILE *file = fopen(filename, "rb");

	if (file == NULL)
	{
		perror("File opening failed");
		return;
	}
	fseek(file, 0, SEEK_END);
	long filesize = ftell(file);

	fseek(file, 0, SEEK_SET);
	fclose(file);

	struct stat file_stat;

	if (stat(filename, &file_stat) == -1)
	{
		perror("Stat failed");
		return;
	}

	snprintf(metadata, 256, "Filename: %s, Size: %ld bytes, Creation Time: %ld", filename, filesize, file_stat.st_ctime);
}

int verify_blockchain(Block *head)
{
	Block* current_block = head;

	while (current_block->next != NULL)
	{
		Block *next_block = current_block->next;

		/*  Verify the hash of the current block */
		char temp[1024];

		snprintf(temp, sizeof(temp), "%d%s%s%s", current_block->index, current_block->previous_hash, current_block->timestamp, current_block->data);
		unsigned char hash[SHA256_DIGEST_LENGTH];

		SHA256((unsigned char *)temp, strlen(temp), hash);
		char computed_hash[SHA256_DIGEST_LENGTH * 2 + 1];

		for (int i = 0; i < SHA256_DIGEST_LENGTH; ++i)
			sprintf(computed_hash + (i * 2), "%02x", hash[i]);

		if (strcmp(current_block->hash, computed_hash) != 0)
			return 0; /*  Tampering detected */

		/* Verify the hash chain: current block's hash should be equal to next block's previous_hash */
		if (strcmp(current_block->hash, next_block->previous_hash) != 0)
			return (0); /* Tampering detected */

		current_block = next_block;
	}
	return (1); /* No tampering */
}


void tamper_block(Block *block)
{
	strcpy(block->data, "Tampered Data");
	char temp[1024];

	snprintf(temp, sizeof(temp), "%d%s%s%s", block->index, block->previous_hash, block->timestamp, block->data);
	unsigned char hash[SHA256_DIGEST_LENGTH];

	SHA256((unsigned char *)temp, strlen(temp), hash);
	for (int i = 0; i < SHA256_DIGEST_LENGTH; ++i)
		sprintf(block->hash + (i * 2), "%02x", hash[i]);
}


void print_blockchain(Block *head)
{
	Block *current_block = head;

	while (current_block != NULL)
	{
		printf("Block %d\n", current_block->index);
		printf("Previous Hash: %s\n", current_block->previous_hash);
		printf("Timestamp: %s\n", current_block->timestamp);
		printf("Data: %s\n", current_block->data);
		printf("Hash: %s\n\n", current_block->hash);
		current_block = current_block->next;
	}
}

int main(void)
{
	Blockchain blockchain;

	blockchain.head = create_genesis_block();

	/* Add blocks with file metadata */
	char metadata[256];

	get_file_metadata("example.txt", metadata);
	Block *second_block = add_block(blockchain.head, metadata);

	get_file_metadata("example2.txt", metadata);
	Block *third_block = add_block(second_block, metadata);

	/* Print blockchain */
	print_blockchain(blockchain.head);

	/*  Verify blockchain */
	printf("Blockchain integrity: %s\n", verify_blockchain(blockchain.head) ? "Valid" : "Invalid");

	/* Tamper with the second block */
	tamper_block(second_block);

	/* Print tampered blockchain */
	print_blockchain(blockchain.head);

	/* Verify blockchain again */
	printf("Blockchain integrity after tampering: %s\n", verify_blockchain(blockchain.head) ? "Valid" : "Invalid");

	return (0);
}
