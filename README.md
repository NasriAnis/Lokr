## Presentation
Secure Password Manager project I'am currently working on, implementing hash and encryption algorithms to store passwords and keys securely.

Note : For now only the CLI partially works (since I'am still working on this project) but a GUI version will be created for a better usability.

## Project structure
In the `src` folder all the source code for the functions used in the CLI tool inside the `cli` folder. Header files are in `include` folder.

## Dependencies
For the CLI tool to work you need to have both `argon2` and `sodium` libraries in your system, for the GUI `GTK4` is needed. Make sure to have the right dependencies before building the project.

## Building the project
You can close this repository and build it using the command `make` inside the root project folder.

## Usage
When first running the program it scans for a `user.bin` file where user credentials are stored then asks you for your password (that will be saved in this `user.bin` file and used as an encryption key) and username, then you can add and see stored passwords using the commands :

```
add [site] [username] [password]
show site=[site] or user=[username]
```

Other options will be added in future versions...
