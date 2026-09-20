# Task 2 (Password Validation and Regex)

## IMPORTANT Note

You can right click the tab and press `Open Preview` to create a preview of the markdown on VScode. (So you don't have to read raw markdown)

## Focus/Aims

This task will focus on testing your skills on:

- Basic C (loop and if conditions)
- Array Manipulation
- C String

This task is mainly focused ~~(loosely based)~~ on data validation (Similar concepts will be very useful when you deal with sensors later on).

## Part A: Parametrised validation

## i) Password checker

We will start with some sort of warmup.

```int password_check(char* password)```  
Complete the function above in `Task2.c`.

>The function will process the C string `password` and return 0 or 1 based on whether the password is valid or not.

The following requirements must be fulfilled:

- The password must be at least **8** characters long, and no longer than **24** characters. (aka the password must be 8-24 characters long, inclusive)
- The password *must only include** the following:
  - Capital Latin letters (A-Z)
  - Small Latin letters (a-z)
  - Digits (0-9)
  - Valid special characters (`~ ! @ # $ % ^ & * ( ) - _ + = { } [ ] \ | ; : " ' < > , . / ?`)
- The password must contain **at least one character** from **each of the four** categories above.
  - If you didn't notice, they are all valid ASCII characters.
- Return `1` if all conditions are met, otherwise `0`.

### Examples

>Invalid passwords (return 0)

- `Abc123!`
  - Too short (7 characters long)
- `AbCdEfGhIjKlMn0P!!!!!!!!!`
  - Too long (25 characters long)
- `helloworld123`
  - No uppercase letter or special character
- `He!l0 world`
  - Whitespace is not a valid special character

>Valid passwords (return 1)

- S0ftwareTutorial*
- H3!!0world

### Assumptions (2A(i))

- All test cases will only use valid ASCII characters.
- The test cases will be at most 512 characters long, and will not be empty.

## ii) Email checker

This one will have slightly more complicated rules, but does the same thing basically.

>```void email_check(char* email)```  
>Complete the function above in `Task2.c`.

The function will process a C string `email` and based on whether the email address is valid or not, it outputs the validity and the parsed values of the mailbox and domain.

Disclaimer: some of the parts of the rules is kinda obsolete in the official modern standards, but it'll be fun to test your skills :\) (The rules are loosely based on the actual RFC 5322 standards.)

### Validation

The email address must follow the format of `<local-part>@<domain>`, where the `<>` can be replaced by a string of characters.

#### \<local-part\>

>The `local-part` of an email address basically indicates who the email will be sent to (basically the receiver of the email).  
>The email sent to the email address will be sent to the mailbox with the name indicated in `local-part`, after removing quotes, tags, and comments (those will be mentioned later).

The `local-part` must follow the rules below:

- The raw local-part string (the part before the @ in the input) must be 1 to 64 characters long.
  - This length includes all outer quotation marks, backslashes, parentheses `()` and their inner content, even though these are stripped later for the final mailbox.
- The length of the **VALID** mailbox indicated by the local-part must not be empty. (See output for definition of mailbox)

**Unquoted**:

- The local-part is defined as 'unquoted' if it does not start and end with the `"` character.
- The following rules apply when the local-part is unquoted:
  - It may include any capital/small Latin letter, and any digit.
  - It may include the characters ```! # $ % & ' * + - / = ? ^ _ ` { | } ~```
  - The `.` character can be included, but it cannot be leading/trailing, nor can they appear consecutively.
    - (`.username@email.com`,`username.@email.com`,`user..name@email.com` are all **not** allowed)

**Quoted**:

- The local-part is defined as `quoted` if the entire string **BOTH** starts and ends with the `"` character. (e.g. `"username"@email.com`)
- The following rules apply to the quoted string (the part quoted by the `"` characters excluding the outer `"` characters) when the local-part is **quoted**:
  - It may include any characters allowed in the unquoted restrictions.
  - The characters `" ( ) , : ; < > @ [ \ ]` are also allowed.
    - For the characters `"` and `\` to be used, the `\` character is used as an escape operator.
      - `\"` represents a literal `"`.
      - `\\` represents a literal `\` (a literal backslash).
      - `"user"name\lol"@email.com` is invalid, but `"user\"name\\me"@email.com` is valid.
    - Whitespaces are allowed unless it is preceded by an unescaped backslash.
      - `\\ `@email.com is valid (because the `\\` represents a literal backslash).
      - `\\\ `@email.com is invalid (the string is parsed as `\\` + `\ `, so the whitespace is invalid).
    - The escape operator `\` is not a part of the mailbox, and will be removed during the output phase.

Tags:

- Tags only exist in **unquoted local-parts** and defined by a string starting with a `+` character. (e.g. `username+tag@email.com`, where `username` is the mailbox and `tag` is the tag)
- If an unquoted local-part contains a `+`, the first `+` acts as the tag delimiter.
  - Everything before this first `+` belongs to the mailbox prefix.
  - Everything after this first `+` is the tag (which may contain additional `+` characters).
- The contents of the tag must also follow the restrictions of the unquoted part. (e.g  `username+ta;g@abc.com` is invalid because `;` cannot exist in unquoted local-parts.)
- Tags are not a part of the mailbox, and will be removed during the output phase.

#### \<domain\>

>The `domain` of an email address is basically the address of the receiver.

The `domain` must follow the rules below:

- The domain must be at most 253 characters. (<=253)
- The domain must only include capital/small Latin letters, digits, hyphens `-`, and dots `.`.
- The domain is separated by dots `.` into subdomains.
- Subdomain rules:
  - Subdomains must not be empty.
  - They must not start or end in hyphens `-`.
  - Subdomains must be at most 63 characters. (<=63)
  - The last subdomain (the most right most one, also known as the top-level domain) must be at least 2 characters long, and can only include letters.

### Outputs (2A(ii))

>The output of the function should clearly output the mailbox and domain of the email address.

The function should output the following: (if the input of the function is `username@email.com`)

```console
The email username@email.com is valid.
Mailbox: username
Domain: email.com
```

Unquoted local-parts and domains are **case insensitive**. So the output will reflect that: (if the input of the function is `HelloWorld@Email.Com`)

```console
The email HelloWorld@Email.Com is valid.
Mailbox: helloworld
Domain: email.com
```

Quoted local-parts will take the literal string inside quotations as the mailbox, excluding all backslash operators: (if the input of the function is `"h$>>o\"WOrld\\"@gmail.com`)

```console
The email "h$>>o\"WOrld\\"@gmail.com is valid.
Mailbox: h$>>o"WOrld\
Domain: gmail.com
```

For invalid emails: (if the input of the function is `"l"l"@email.com`, which is invalid due to a `"` without a '\' operator)

```console
The email "l"l"@email.com is invalid.
```

If the input is `hello@world.123` (invalid due to the top-level domain rule)

```console
The email hello@world.123 is invalid.
```

#### Comments

Comments can be included in the email address, in both the local-part and the domain part.

- `(hello)username@domain.com` is treated like `username@domain.com`.
- `user(hello)name@domain.com` is also valid, and is treated as `username@domain.com`. (The comment is removed, and the remaining parts are concatenated.)

They are defined by starting with a `(` character, and ending with a `)` character.  
Comments cannot exist within quoted local-parts. (For the email `"user(n)ame"@email.com`, the `(n)` is not treated as a comment, but as a literal string.)

The content inside comments will be ignored during both the validation step and the output step.

Examples:

Input: `fu(happy)n+things@yahoo.com`

```console
The email fu(happy)n+things@yahoo.com is valid.
Mailbox: fun
Domain: yahoo.com
```

Input: `"foo+bar(n)"@abc.co.uk`

```console
The email "foo+bar(n)"@abc.co.uk is valid.
Mailbox: foo+bar(n)
Domain: abc.co.uk
```

### Assumptions (2A(ii))

- All test cases will be at most 500 characters long.
- The test cases will only use valid ASCII characters.

## Part B: Modified Regex (Custom Regex on Letters)

Regex, also known as regular expressions, is a string of characters that indicates a pattern in a string/input. It is regularly used in data validation that includes strings.  
>For this bonus task, you are required to parse a regex, and print out strings that follows the patterns.

`void regex(char** list, char* regex)`  
Complete the function provided in Task2.h

List will contain an array of C strings (single word, null terminated, no whitespaces), each of varying length. The function will print out all the strings in the list that satisfies the regex (in the same order of the list).  

### Regex metacharacters

>The test cases will only include the metacharacters listed.

#### Conditions

| Expression | Name | What it does | Example Match |
| :--- | :--- | :--- | :--- |
| `.` | Dot (Wildcard) | Matches **any single character** | `c.t` matches `"cat"`, `"cut"`, and `"cot"`. |
| `[abc]` | Custom Set | Matches exactly **one** character from the list inside. | `h[aeiou]llo` matches `"e"` in `"hello"`. |
| `[^abc]` | Negated Set | Matches exactly **one** character **not** in the list. | `[^aeiou]ello` matches `"h"` in `"hello"`. |
| `[a-z]` | Range | Matches one character within the alphabetical/numerical range. | `[a-z]ello` matches `"h"` in `"hello"`. |

#### Quantifiers

| Expression | Name | What it does | Example Match |
| :--- | :--- | :--- | :--- |
| `*` | Star (0 or more) | Matches **0 or more** repetitions. | `ca*t` matches `"ct"`, `"cat"`, and `"caat"`. |
| `+` | Plus (1 or more) | Matches **1 or more** repetitions. | `ca+t` matches `"cat"` and `"caat"`, but **not** `"ct"`. |
| `?` | Question (0 or 1) | Matches **0 or 1** repetition (makes it optional). | `colou?r` matches `"color"` and `"colour"`. |
| `{n}` | Exact | Matches exactly **n** times. | `a{3}` matches `"aaa"` but not `"aa"`. |
| `{n,}` | At least n | Matches **n or more** times. | `a{2,}` matches `"aa"` and `"aaaaa"`. |
| `{n,m}` | Between | Matches between **n** and **m** times. | `a{2,4}` matches `"aa"`, `"aaa"`, and `"aaaa"`. |

#### Special

| Expression | Name | What it does | Example Match |
| :--- | :--- | :--- | :--- |
| `(abc)` | Capturing Group | Treats inside as one unit.\* | `(ha)+` matches `"ha"`, `"haha"`, `"hahaha"`. |

\*Groups ( ... ) can contain any combination of other metacharacters (dots, character classes, quantifiers, and even nested groups, though nested groups will not appear in the test cases). The group acts as a single unit for the quantifiers that follow it.  

**NOTE**: In this task, the entire string must match the regex. So, `e.t` would match `eat` but not `beat` or `underneath`.

### How Regex works

The metacharacter work like building blocks, and they will correspond to characters in a string. You can also mix and match the operators to create different filters/matches.  

Something like `c.t` would match to any string that has `c` as its first character, and `t` as its third character. Since `.` is the wildcard operator, it can match to any character. So, examples that match to `c.t` is `cat`, `cot`, `cut`, and even `cvt` (it doesn't have to be a valid word).  
You can also mix and match operators, like `([^aeiou][aeiou])+[^aeiou]?` looks for all strings with starts with a consonant, and halternates vowels and consonants. (e.g `no`, `cane`, `bat`, `babababababababababa`)

### Output (2B)

Here are a few examples.  

Input: list = {"cat", "cot", "cow", "cut", "mop", "mart", "cart", "content"}, regex = "c.*t"

```console
Regex = c.*t
Results:
cat
cot
cut
cart
content
```

Input: list = {"dog", "dodog", "dododog", "dg", "dag", "do", "g"}, regex = "(do)+g"

```console
Regex = (do)+g
Results:
dog
dodog
dododog
```

Input: list = {"cat", "cut", "cot", "cbt", "c0t", "ct"}, regex = "c[^a]t"

```console
Regex = c[^a]t
Results:
cut
cot
cbt
c0t
```

list = {"bat", "bath", "baths", "b", "ba", "battles"}, regex = "b[a-z]{2,3}"

```console
Regex = b[a-z]{2,3}
Results:
bat
bath
```

### Assumptions (2B)

- All strings within list only contain small Latin letters (aka lowercase letters, a-z).
- You may assume that the list and regex will not be empty, and the regex is always valid (no incorrect syntax).
- The regex format strictly follows `<condition>``<quantifier>` pairs, with groups counting as conditions.

## Compiling & Testing

----------------- WIP -------------------------
