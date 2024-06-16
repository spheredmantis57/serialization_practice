# Overview

This repo is a small test for serialization and deserialization.

Most of this was written by chatgpt and will need to be further reviewed once I have time.
Due to this, I know the solution works upon good input, but will definitely need to be reviewed and changed to be a good solution to provide at the end of the practice.

Until that happens, the validator and instructions should be solid enough to provide to give guidance to the developer.

This can be validated by:
1. Compiling the solution
```sh
$ gcc solution -o your program
```
2. Create the test files
```sh
python3 generator.py --num 1
```
3. Running the test
```sh
$ pytest validator.py -s
========================== test session starts ==========================
platform linux -- Python 3.8.10, pytest-8.2.0, pluggy-1.5.0
rootdir: /home/green/repos/review_repos/serialize/serialization_practice
collected 3 items

validator.py ...

========================== 3 passed in 0.01s ==========================
```
