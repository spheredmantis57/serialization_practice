import argparse
import struct
import random
import string
import os
import json

# Define the data structures
class Person:
    TYPE_ID = 1

    def __init__(self, person_id, age, name, bio):
        self.person_id = person_id
        self.age = age
        self.name = name
        self.bio = bio

    def serialize(self):
        name_bytes = self.name.encode('utf-8')
        bio_bytes = self.bio.encode('utf-8')
        packet = struct.pack('>B I B B', self.TYPE_ID, self.person_id, self.age, len(name_bytes)) + name_bytes + struct.pack('>B', len(bio_bytes)) + bio_bytes
        return struct.pack('>I', len(packet)) + packet

    def to_dict(self):
        return {
            "ID": self.person_id,
            "Age": self.age,
            "Name": self.name,
            "Bio": self.bio
        }

class Book:
    TYPE_ID = 2

    def __init__(self, isbn, pages, title, author):
        self.isbn = isbn
        self.pages = pages
        self.title = title
        self.author = author

    def serialize(self):
        title_bytes = self.title.encode('utf-8')
        author_bytes = self.author.encode('utf-8')
        packet = struct.pack('>B 13s I B', self.TYPE_ID, self.isbn.encode('utf-8'), self.pages, len(title_bytes)) + title_bytes + struct.pack('>B', len(author_bytes)) + author_bytes
        return struct.pack('>I', len(packet)) + packet

    def to_dict(self):
        return {
            "ISBN": self.isbn,
            "Pages": self.pages,
            "Title": self.title,
            "Author": self.author
        }

class Product:
    TYPE_ID = 3

    def __init__(self, product_id, price, name, description):
        self.product_id = product_id
        self.price = price
        self.name = name
        self.description = description

    def serialize(self):
        name_bytes = self.name.encode('utf-8')
        description_bytes = self.description.encode('utf-8')
        packet = struct.pack('>B I H B', self.TYPE_ID, self.product_id, self.price, len(name_bytes)) + name_bytes + struct.pack('>B', len(description_bytes)) + description_bytes
        return struct.pack('>I', len(packet)) + packet

    def to_dict(self):
        return {
            "Product ID": self.product_id,
            "Price": self.price,
            "Name": self.name,
            "Description": self.description
        }

def generate_random_string(length):
    return ''.join(random.choices(string.ascii_letters + string.digits, k=length))

def create_test_files(num_files):
    os.makedirs('test_files', exist_ok=True)

    for i in range(1, num_files + 1):
        person = Person(random.randint(10000, 99999), random.randint(1, 100), generate_random_string(random.randint(5, 25)), generate_random_string(random.randint(5, 25)))
        book = Book(generate_random_string(13), random.randint(100, 1000), generate_random_string(random.randint(5, 25)), generate_random_string(random.randint(5, 25)))
        product = Product(random.randint(10000, 99999), random.randint(1, 100), generate_random_string(random.randint(5, 25)), generate_random_string(random.randint(5, 25)))

        with open(f'test_files/person_{i}.dat', 'wb') as f:
            f.write(person.serialize())

        with open(f'test_files/book_{i}.dat', 'wb') as f:
            f.write(book.serialize())

        with open(f'test_files/product_{i}.dat', 'wb') as f:
            f.write(product.serialize())

        with open(f'test_files/person_{i}.json', 'w') as f:
            json.dump(person.to_dict(), f, indent=4)

        with open(f'test_files/book_{i}.json', 'w') as f:
            json.dump(book.to_dict(), f, indent=4)

        with open(f'test_files/product_{i}.json', 'w') as f:
            json.dump(product.to_dict(), f, indent=4)

if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="Generate test files for serialization and deserialization practice.")
    parser.add_argument('--num', type=int, required=True, help="Number of test files to create for each type")

    args = parser.parse_args()
    create_test_files(args.num)