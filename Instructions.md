<!-- Generated with ChatGPT, then edited and added to -->

# Serialization and Deserialization Practice

This repository contains a training exercise for practicing serialization and deserialization of custom data structures. The objective is to read serialized data from a file, deserialize it, print the information in a specific format, serialize the data again, and write it to a new file for comparison.

## Structures

There are three data structures: Person, Book, and Product. Each data structure includes both fixed-length and variable-length fields and is prefixed with a type identifier. All data fields are stored in big-endian format.

### Layout of Each Type
1. Person

```
Packet Size: 4 bytes (uint32_t, big-endian)
Type ID: 1 byte (value: 1)
ID: 4 bytes (uint32_t, big-endian)
Age: 1 byte (uint32_t)
Name: Variable length (string, prefixed with 1 byte indicating length)
Bio: Variable length (string, prefixed with 1 byte indicating length)
```

2. Book

```
Packet Size: 4 bytes (uint32_t, big-endian)
Type ID: 1 byte (value: 2)
ISBN: 13 bytes (fixed-length string)
Pages: 4 bytes (uint32_t, big-endian)
Title: Variable length (string, prefixed with 1 byte indicating length)
Author: Variable length (string, prefixed with 1 byte indicating length)
```

3. Product

```
Packet Size: 4 bytes (uint32_t, big-endian)
Type ID: 1 byte (value: 3)
Product ID: 4 bytes (uint32_t, big-endian)
Price: 4 bytes (uint16_t, big-endian)
Name: Variable length (string, prefixed with 1 byte indicating length)
Description: Variable length (string, prefixed with 1 byte indicating length)
```

### Printing Format

When you deserialize a data structure, you should print the information in the following format:

#### Person

```
Person:
ID: <person_id>
Age: <age>
Name: <name>
Bio: <bio>
```

#### Book

```
Book:
ISBN: <isbn>
Pages: <pages>
Title: <title>
Author: <author>
```

#### Product

```
Product:
Product ID: <product_id>
Price: <price>
Name: <name>
Description: <description>
```

## Task Instructions

1. Read Serialized Data: Read the serialized data from the provided file.
2. Deserialize: Deserialize the data based on the type identifier and convert from big-endian format where applicable.
3. Print Information: Print the deserialized information in the specified format.
4. Serialize Again: Serialize the data back into its original format and convert to big-endian format where applicable.
5. Write to New File: Write the re-serialized data to a new file.

### Example Usage

The repository includes several test files with serialized data for Person, Book, and Product. Your task is to create a program that will read these files, perform the steps outlined above.

```sh
$ ./program test_files/book_1.dat
$ cmp book_1.dat out.dat  # should match
```

### Validation

You can use pytest to compare the original files with the output files to ensure correctness. Each output file should be identical to its corresponding input file if the serialization and deserialization processes are implemented correctly.

By following these instructions, you'll gain practical experience with serialization and deserialization, and ensure your implementation is correct by comparing the output files to the original ones.