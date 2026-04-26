## Presentation
Secure Password Manager project I'am currently working on, implementing hash and encryption algorithms to store passwords and keys securely.

## Project structure
In the `src` folder all the source code for the functions used in the CLI tool inside the `cli` folder and for the GUI application inside the `gui` folder. Header files are in `include` folder inside both `cli` and `gui`, as well as other features and wrapper functions inside the `features` folder in `src` and `gui`.

## Dependencies
For the CLI tool to work you need to have both `argon2` and `sodium` libraries in your system, for the GUI `GTK4` is needed. Make sure to have the right dependencies before building the project.

## Building the project
You can clone this repository and build it using the command `make` inside the root project folder for the CLI and `make gui` for the GUI app.

## CLI Usage
When first running the program it scans for a `user.bin` file where user credentials are stored then asks you for your password (that will be saved in this `user.bin` file and used as an encryption key) and username, then you can add and see stored passwords using the commands :

```
add [site] [username] [password]
show site=[site] or user=[username]
delete [site] [username]
dump-all
```

Other options will be added in future versions...
