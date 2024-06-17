/*
Written by ChatGPT then modified. This is only modified to work on happy path.
Note this is not provided and was only made to ensure the test was good.
If this were to be used as a example solution, MANY changes would need to be
made for best practices and not to leak memory and bounds checking before
accessing members.
BLUF: AI written for quick and easy solution to make the test. Not good code.
*/
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <endian.h>

// Define structures to match Python serialized data

struct Person {
    uint8_t type_id;
    uint32_t total_sz;
    uint32_t person_id;
    uint8_t age;
    uint8_t name_len;
    char *name;
    uint8_t bio_len;
    char *bio;
};

struct Book {
    uint8_t type_id;
    uint32_t total_sz;
    char isbn[13];
    uint32_t pages;
    uint8_t title_len;
    char *title;
    uint8_t author_len;
    char *author;
};

struct Product {
    uint8_t type_id;
    uint32_t total_sz;
    uint32_t product_id;
    uint16_t price;
    uint8_t name_len;
    char *name;
    uint8_t description_len;
    char *description;
};

// Function to deserialize Person from file
void deserialize_person(FILE *fp, struct Person *person) {
    person->type_id = 1;
    fread(&person->person_id, sizeof(uint32_t), 1, fp);
    person->total_sz += sizeof(uint32_t);
    person->person_id = be32toh(person->person_id);
    fread(&person->age, sizeof(uint8_t), 1, fp);
    person->total_sz += sizeof(uint8_t);
    fread(&person->name_len, sizeof(uint8_t), 1, fp);
    person->total_sz += sizeof(uint8_t);

    person->name = malloc(person->name_len + 1);
    fread(person->name, sizeof(char), person->name_len, fp);
    person->total_sz += person->name_len;
    person->name[person->name_len] = '\0';

    fread(&person->bio_len, sizeof(uint8_t), 1, fp);
    person->total_sz += sizeof(uint8_t);

    person->bio = malloc(person->bio_len + 1);
    fread(person->bio, sizeof(char), person->bio_len, fp);
    person->total_sz += person->bio_len;
    person->bio[person->bio_len] = '\0';
}

// Function to deserialize Book from file
void deserialize_book(FILE *fp, struct Book *book) {
    book->type_id = 2;
    fread(book->isbn, sizeof(char), 13, fp);
    book->total_sz += 13;
    fread(&book->pages, sizeof(uint32_t), 1, fp);
    book->total_sz += sizeof(uint32_t);
    book->pages = be32toh(book->pages);
    fread(&book->title_len, sizeof(uint8_t), 1, fp);
    book->total_sz += sizeof(uint8_t);

    book->title = malloc(book->title_len + 1);
    fread(book->title, sizeof(char), book->title_len, fp);
    book->total_sz += book->title_len;
    book->title[book->title_len] = '\0';

    fread(&book->author_len, sizeof(uint8_t), 1, fp);
    book->total_sz += sizeof(uint8_t);

    book->author = malloc(book->author_len + 1);
    fread(book->author, sizeof(char), book->author_len, fp);
    book->total_sz += book->author_len;
    book->author[book->author_len] = '\0';
}

// Function to deserialize Product from file
void deserialize_product(FILE *fp, struct Product *product) {
    product->type_id = 3;
    fread(&product->product_id, sizeof(uint32_t), 1, fp);
    product->total_sz += sizeof(uint32_t);
    product->product_id = be32toh(product->product_id);
    fread(&product->price, sizeof(uint16_t), 1, fp);
    product->total_sz += sizeof(uint16_t);
    product->price = be16toh(product->price);
    fread(&product->name_len, sizeof(uint8_t), 1, fp);
    product->total_sz += sizeof(uint8_t);

    product->name = malloc(product->name_len + 1);
    fread(product->name, sizeof(char), product->name_len, fp);
    product->total_sz += product->name_len;
    product->name[product->name_len] = '\0';

    fread(&product->description_len, sizeof(uint8_t), 1, fp);
    product->total_sz += sizeof(uint8_t);

    product->description = malloc(product->description_len + 1);
    fread(product->description, sizeof(char), product->description_len, fp);
    product->total_sz += product->description_len;
    product->description[product->description_len] = '\0';
}

// Function to serialize Person to file
void serialize_person(struct Person *person, FILE *fp) {
    person->total_sz = htobe32(person->total_sz);
    fwrite(&person->total_sz, sizeof(uint32_t), 1, fp);
    fwrite(&person->type_id, sizeof(uint8_t), 1, fp);
    person->person_id = htobe32(person->person_id);
    fwrite(&person->person_id, sizeof(uint32_t), 1, fp);
    fwrite(&person->age, sizeof(uint8_t), 1, fp);
    fwrite(&person->name_len, sizeof(uint8_t), 1, fp);
    fwrite(person->name, sizeof(char), person->name_len, fp);
    fwrite(&person->bio_len, sizeof(uint8_t), 1, fp);
    fwrite(person->bio, sizeof(char), person->bio_len, fp);
}

// Function to serialize Book to file
void serialize_book(struct Book *book, FILE *fp) {
    book->total_sz = htobe32(book->total_sz);
    fwrite(&book->total_sz, sizeof(uint32_t), 1, fp);
    fwrite(&book->type_id, sizeof(uint8_t), 1, fp);
    fwrite(book->isbn, sizeof(char), 13, fp);
    book->pages = htobe32(book->pages);
    fwrite(&book->pages, sizeof(uint32_t), 1, fp);
    fwrite(&book->title_len, sizeof(uint8_t), 1, fp);
    fwrite(book->title, sizeof(char), book->title_len, fp);
    fwrite(&book->author_len, sizeof(uint8_t), 1, fp);
    fwrite(book->author, sizeof(char), book->author_len, fp);
}

// Function to serialize Product to file
void serialize_product(struct Product *product, FILE *fp) {
    product->total_sz = htobe32(product->total_sz);
    fwrite(&product->total_sz, sizeof(uint32_t), 1, fp);
    fwrite(&product->type_id, sizeof(uint8_t), 1, fp);
    product->product_id = htobe32(product->product_id);
    fwrite(&product->product_id, sizeof(uint32_t), 1, fp);
    product->price = htobe16(product->price);
    fwrite(&product->price, sizeof(uint16_t), 1, fp);
    fwrite(&product->name_len, sizeof(uint8_t), 1, fp);
    fwrite(product->name, sizeof(char), product->name_len, fp);
    fwrite(&product->description_len, sizeof(uint8_t), 1, fp);
    fwrite(product->description, sizeof(char), product->description_len, fp);
}

int main(int argc, char *argv[]) {
    int ret = EXIT_FAILURE;
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <file_path>\n", argv[0]);
        goto END;
    }

    char *file_path = argv[1];
    FILE *fp = fopen(file_path, "rb");
    if (!fp) {
        perror("Error opening file");
        goto END;
    }

    fseek(fp, 0, SEEK_END);
    long file_size = ftell(fp);
    fseek(fp, 0, SEEK_SET);

    while (ftell(fp) < file_size) {
        uint32_t size;
        fread(&size, sizeof(uint32_t), 1, fp);

        // todo read in entire packet and do pointer arithmetic and bounds checking
        // uint8_t *packet = calloc(size, 1);
        // if (NULL == packet)
        // {
        //     goto END;
        // }

        uint8_t type_id;
        fread(&type_id, sizeof(uint8_t), 1, fp);

        switch (type_id) {
            case 1: {
                struct Person person = {.total_sz = 1}; // already have the type
                deserialize_person(fp, &person);

                printf("Person:\n");
                printf("ID: %u\n", person.person_id);
                printf("Age: %u\n", person.age);
                printf("Name: %s\n", person.name);
                printf("Bio: %s\n", person.bio);

                // Serialize person to out.dat
                FILE *out_fp = fopen("out.dat", "ab");
                if (!out_fp) {
                    perror("Error opening out.dat for writing");
                    goto END;
                }
                serialize_person(&person, out_fp);
                fclose(out_fp);

                free(person.name);
                free(person.bio);
                break;
            }

            case 2: {
                struct Book book = {.total_sz = 1}; // already have the type
                deserialize_book(fp, &book);

                printf("Book:\n");
                printf("ISBN: %s\n", book.isbn);
                printf("Pages: %u\n", book.pages);
                printf("Title: %s\n", book.title);
                printf("Author: %s\n", book.author);

                // Serialize book to out.dat
                FILE *out_fp = fopen("out.dat", "ab");
                if (!out_fp) {
                    perror("Error opening out.dat for writing");
                    goto END;
                }
                serialize_book(&book, out_fp);
                fclose(out_fp);

                free(book.title);
                free(book.author);
                break;
            }

            case 3: {
                struct Product product = {.total_sz = 1}; // already have the type
                deserialize_product(fp, &product);

                printf("Product:\n");
                printf("Product ID: %u\n", product.product_id);
                printf("Price: %u\n", (unsigned int)product.price);
                printf("Name: %s\n", product.name);
                printf("Description: %s\n", product.description);

                // Serialize product to out.dat
                FILE *out_fp = fopen("out.dat", "ab");
                if (!out_fp) {
                    perror("Error opening out.dat for writing");
                    goto END;
                }
                serialize_product(&product, out_fp);
                fclose(out_fp);

                free(product.name);
                free(product.description);
                break;
            }

            default:
                fprintf(stderr, "Unknown type_id: %u\n", type_id);
                break;
        }
    }

END:
    if (NULL != fp)
    {
        fclose(fp);
    }
    return EXIT_SUCCESS;
}

