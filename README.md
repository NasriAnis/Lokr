## Presentation
Secure Password Manager project I'am currently working on, implementing hash and encryption algorithms to store passwords and keys securely.

Note : For now only the CLI partially works (since I'am still working on this project) but a GUI version will be created for a better usability.

## Project structure
In the `src` folder all the source code for the functions used in the CLI tool inside the `cli` folder. Header files are in `include` folder.

## Usage
You can close this repository and build it using the command `make` inside the root project folder. Dependencies include `sodium` and `argon2` libraries for now.

When first running the program it scans for a `user.bin` file where user credentials are stored then asks you for your password (that will be saved in this `user.bin` file and used as an encryption key) and username, then you can add and see stored passwords using the commands :

```
add [site] [username] [password]
show [site] or [username] or both
```

Other options will be added in future versions...

## Contributing
Feel free to contribute and make this project better, thanks in advance.
