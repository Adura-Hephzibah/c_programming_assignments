// SPDX-License-Identifier: MIT
pragma solidity ^0.8.0;

contract PropertyTitle {
    struct Property {
        uint256 id;
        address owner;
        string details;
    }

    mapping(uint256 => Property) public properties;
    uint256 public nextPropertyId;

    event PropertyRegistered(uint256 indexed id, address indexed owner, string details);
    event PropertyTransferred(uint256 indexed id, address indexed oldOwner, address indexed newOwner);

    // Modifier to restrict actions to property owners
    modifier onlyPropertyOwner(uint256 propertyId) {
        require(properties[propertyId].owner == msg.sender, "Only the owner can perform this action");
        _;
    }

    // Register a new property with unique ID
    function registerProperty(string memory details) public {
        uint256 uniqueId = uint256(keccak256(abi.encodePacked(block.timestamp, nextPropertyId)));
        properties[uniqueId] = Property(uniqueId, msg.sender, details);
        emit PropertyRegistered(uniqueId, msg.sender, details);
        nextPropertyId++;
    }

    // Verify the ownership of a property
    function verifyOwnership(uint256 propertyId) public view returns (address) {
        return properties[propertyId].owner;
    }

    // Transfer the property to a new owner
    function transferProperty(uint256 propertyId, address newOwner) public onlyPropertyOwner(propertyId) {
        address oldOwner = properties[propertyId].owner;
        properties[propertyId].owner = newOwner;
        emit PropertyTransferred(propertyId, oldOwner, newOwner);
    }
}
