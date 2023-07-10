# rpwdg - Random Password Generator
Simple random password generator.

## Description:
rpwdg is a command line app that generates random passwords of various lengths and characters. It can be used to create secure and unique passwords for different accounts or purposes.

## Usage:
```bash
  rpwdg (-h|-v|-L <length> [-u][-d][-s]...)
```

### Arguments:
**length**  Specify the length of the password, between 4 and 16.

### Options:
**-h, --help**    Show this help message and exit.

**-v, --version** Show the app version and exit.

**-L, --length**  Use this option to specify the length of the password. This option is mutually exclusive with the -h and -v options. If used, it must be followed by a valid length argument.

**-u, --upper**   Include uppercase letters in the password. This option is only valid when the -L option is used. It can be combined with the -d and/or -s options in any order or grouping.

**-d, --digits**  Include digits in the password. This option is only valid when the -L option is used. It can be combined with the -u and/or -s options in any order or grouping.

**-s, --special** Include special characters in the password. This option is only valid when the -L option is used. It can be combined with the -u and/or -d options in any order or grouping.

### Examples:

Show a help message and exit.
```bash 
rpwdg -h
```          

Show the app version and exit.
```bash 
rpwdg -v
```

Generate a random password of 8 characters, using lowercase letters only.
```bash 
rpwdg -L 8
```

Generate a random password of 12 characters, using lowercase letters only.
```bash
rpwdg -L 12
```

Generate a random password of 10 characters, using lowercase and uppercase letters.
```bash
rpwdg -L 10 -u
```

Generate a random password of 16 characters, using lowercase letters and digits.
```bash
rpwdg -L 16 -d
```

Generate a random password of 14 characters, using lowercase letters and special characters.
```bash
rpwdg -L 14 -s
```

Generate a random password of 8 characters, using lowercase, uppercase, digits, and special characters.
```bash 
rpwdg -L 8 -uds
```

**Note:** The order and grouping of the -u, -d, and -s options do not matter. For example, rpwdg -L 4 -u -d is equivalent to rpwdg -L 4 -ud.

