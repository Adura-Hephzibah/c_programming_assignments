const readlineSync = require('readline-sync');
const forge = require('node-forge');

// Utility function to calculate hash
function calculateHash(index, previousHash, timestamp, transactions, nonce) {
  const sha256 = forge.md.sha256.create();
  sha256.update(index + previousHash + timestamp + JSON.stringify(transactions) + nonce);
  return sha256.digest().toHex();
}

// Generate a new key pair
function generateKeyPair() {
  const keys = forge.pki.rsa.generateKeyPair(2048);
  const publicKeyPem = forge.pki.publicKeyToPem(keys.publicKey);
  const privateKeyPem = forge.pki.privateKeyToPem(keys.privateKey);
  return { publicKey: publicKeyPem, privateKey: privateKeyPem };
}

// Transaction class
class Transaction {
  constructor(paymentID, studentID, sessionID, amount) {
    this.paymentID = paymentID;
    this.studentID = studentID;
    this.sessionID = sessionID;
    this.amount = amount;
    this.signature = null;
  }

  // Method to create a digital signature
  signTransaction(signingKeyPem) {
    const signingKey = forge.pki.privateKeyFromPem(signingKeyPem);
    const hashTx = this.calculateHash();
    const md = forge.md.sha256.create();
    md.update(hashTx);
    this.signature = signingKey.sign(md);
  }

  // Method to calculate transaction hash
  calculateHash() {
    const sha256 = forge.md.sha256.create();
    sha256.update(this.paymentID + this.studentID + this.sessionID + this.amount);
    return sha256.digest().toHex();
  }

  // Method to validate transaction
  isValid() {
    if (!this.signature) {
      throw new Error('No signature in this transaction');
    }

    const publicKey = forge.pki.publicKeyFromPem(this.studentID);
    const md = forge.md.sha256.create();
    md.update(this.calculateHash());
    return publicKey.verify(md.digest().bytes(), this.signature);
  }
}

// Block class
class Block {
  constructor(index, timestamp, transactions, previousHash = '', nonce = 0) {
    this.index = index;
    this.timestamp = timestamp;
    this.transactions = transactions;
    this.previousHash = previousHash;
    this.nonce = nonce;
    this.hash = this.calculateHash();
  }

  // Method to calculate block hash
  calculateHash() {
    return calculateHash(this.index, this.previousHash, this.timestamp, this.transactions, this.nonce);
  }

  // Method to mine a block
  mineBlock(difficulty) {
    while (this.hash.substring(0, difficulty) !== Array(difficulty + 1).join("0")) {
      this.nonce++;
      this.hash = this.calculateHash();
    }
    console.log("Block mined: " + this.hash);
  }

  // Method to validate all transactions in the block
  hasValidTransactions() {
    for (const tx of this.transactions) {
      if (!tx.isValid()) {
        return false;
      }
    }
    return true;
  }
}

// Blockchain class
class Blockchain {
  constructor() {
    this.chain = [this.createGenesisBlock()];
    this.difficulty = 4;
    this.pendingTransactions = [];
  }

  // Method to create the genesis block
  createGenesisBlock() {
    const genesisBlock = new Block(0, "01/01/2020", [], "0");
    genesisBlock.hash = calculateHash(0, "0", "01/01/2020", [], 0);
    return genesisBlock;
  }

  // Method to get the latest block
  getLatestBlock() {
    return this.chain[this.chain.length - 1];
  }

  // Method to add a new transaction
  addTransaction(transaction) {
    if (!transaction.paymentID || !transaction.studentID || !transaction.sessionID || !transaction.amount) {
      throw new Error('Transaction must include paymentID, studentID, sessionID and amount');
    }
    if (!transaction.isValid()) {
      throw new Error('Cannot add invalid transaction to chain');
    }
    this.pendingTransactions.push(transaction);
  }

  // Method to mine a new block
  minePendingTransactions() {
    let block = new Block(this.chain.length, Date.now().toString(), this.pendingTransactions, this.getLatestBlock().hash);
    block.mineBlock(this.difficulty);
    this.chain.push(block);
    this.pendingTransactions = [];
  }

  // Method to check the validity of the blockchain
  isChainValid() {
    for (let i = 1; i < this.chain.length; i++) {
      const currentBlock = this.chain[i];
      const previousBlock = this.chain[i - 1];

      if (!currentBlock.hasValidTransactions()) {
        return false;
      }
      if (currentBlock.hash !== currentBlock.calculateHash()) {
        return false;
      }
      if (currentBlock.previousHash !== previousBlock.hash) {
        return false;
      }
    }
    return true;
  }

  // Method to print the blockchain
  printBlockchain() {
    console.log(JSON.stringify(this.chain, null, 4));
  }
}

// CLI for interacting with the blockchain
class CLI {
  constructor() {
    this.blockchain = new Blockchain();
    this.keys = generateKeyPair(); // Store keys in-memory for simplicity
  }

  run() {
    while (true) {
      console.log('1. Initialize a new blockchain');
      console.log('2. Add a new transaction');
      console.log('3. Mine a new block');
      console.log('4. Display the blockchain');
      console.log('5. Generate key pair');
      console.log('6. Show current key pair');
      console.log('7. Exit');

      const choice = readlineSync.question('Enter your choice: ');

      switch (choice) {
        case '1':
          this.blockchain = new Blockchain();
          console.log('New blockchain initialized.');
          break;
        case '2':
          this.addTransaction();
          break;
        case '3':
          this.mineBlock();
          break;
        case '4':
          this.blockchain.printBlockchain();
          break;
        case '5':
          this.generateKeyPair();
          break;
        case '6':
          this.showKeyPair();
          break;
        case '7':
          process.exit();
        default:
          console.log('Invalid choice, please try again.');
      }
    }
  }

  addTransaction() {
    const paymentID = readlineSync.question('Enter payment ID: ');
    const studentID = this.keys.publicKey; // Use stored public key as student ID
    const sessionID = readlineSync.question('Enter session ID: ');
    const amount = readlineSync.question('Enter amount: ');

    const transaction = new Transaction(paymentID, studentID, sessionID, amount);
    try {
      transaction.signTransaction(this.keys.privateKey);
      this.blockchain.addTransaction(transaction);
      console.log('Transaction added.');
    } catch (error) {
      console.error('Failed to add transaction:', error.message);
    }
  }

  mineBlock() {
    console.log('Mining a new block...');
    this.blockchain.minePendingTransactions();
    console.log('Block mined and added to the blockchain.');
  }

  generateKeyPair() {
    this.keys = generateKeyPair();
    console.log('New key pair generated.');
    this.showKeyPair();
  }

  showKeyPair() {
    console.log('Public Key:', this.keys.publicKey);
    console.log('Private Key:', this.keys.privateKey);
  }
}

// Initialize and run the CLI
const cli = new CLI();
cli.run();
