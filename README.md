# Narthex
<img src="https://mcdim.xyz/projects/n/narthexblack.png" alt="Narthex logo" style="height: 150px; width:150px;"/>

<p float="left">
<img src="https://img.shields.io/badge/version-1.2-blue"/>
<img src="https://img.shields.io/badge/language-C-lightgrey"/>
<img src="https://img.shields.io/badge/lines%20of%20code-1k-lightgreen"/>
<img src="https://img.shields.io/badge/tools-8-green"/>
<img src="https://img.shields.io/badge/dependencies-0-green"/>
<img src="https://img.shields.io/badge/license-GNU%20GPLv3-yellow"/>
[![Rawsec's CyberSecurity Inventory](https://inventory.raw.pm/img/badges/Rawsec-inventoried-FF5050_flat.svg)](https://inventory.raw.pm/tools.html#Narthex)
</p>

Narthex (Greek: Νάρθηξ, νάρθηκας) is a modular & minimal dictionary generator for Unix and Unix-like operating system written in C and Shell. It contains autonomous Unix-style programs for the creation of personalised dictionaries that can be used for password recovery & security assessment. The programs make use of Unix text streams for the collaboration with each other, according to the Unix philosophy. It is licensed under the GPL v3.0.

*I made a video to explain the usage of Narthex:*
https://www.youtube.com/watch?v=U0UmCeLJSkk&t=938s
(the timestamp is intentional)

## The tools
+ *nchance*   -  A capitalization tool that appends the results to the bottom of the dictionary.
+ *ninc*      -  A incrementation tool that multiplies alphabetical lines and appends an n++ at the end of each line.
+ *ncom*      -  A combination tool that creates different combinations between the existing lines of the dictionary.
+ *nrev*      -  A reversing tool, that appends the reserved versions of the lines at the end of the dictionary.
+ *nleet*     -  A leetifier. Replaces characters with Leet equivalents, such as @ instead of a, or 3 instead of e.
+ *nclean*    -  A tool for removing passwords that don't meet your criteria (too short, no special characters etc.)
+ *napp*      -  A tool that appends characters or words before or after the lines of the dictionary.
+ *nwiz*      -  A wizard that asks for the infromation and combines the tools together to create a final dictionary.

## Screenshots
<p float="left">
<img src="https://mcdim.xyz/projects/n/screens/narthex2.png" alt="Narthex logo" width=50%/>
<img src="https://mcdim.xyz/projects/n/screens/narthex1.png" alt="Narthex logo" width=38.8%/>
</p>

## Dependencies
**Narthex has no hard dependencies**, however there are two building dependencies, `GCC` and `Make`, which are both required in order to easily compile and install the binaries, but not to run them.

## Install
In order to install, execute the following commands:
```
$ git clone https://github.com/MichaelDim02/Narthex.git && cd Narthex
$ sudo make install
```

## Usage
For easy use, there is a wizard program, nwiz, that you can use. Just run
```
$ nwiz
```
And it will ask you for the target's information & generate the dictionary for you.

## Advanced usage
If you want to make full use of Narthex, you can read the manpages of each tool. What they all do, really, is enhance small dictionaries. They are really minimal, and use Unix text streams to read and output data. For example, save a couple keywords into a textfile ```words.txt``` in a different line each, and run the following
```
$ cat words.txt | nhance -f | ncom | nleet a:@ | ninc 1 30 > dictionary.txt
```
and you'll see the results for yourself. Alterantively, you can try this for a larger and more complicated dictionary:
```
$ cat words.txt | nhance -f | ncom -d .- | ninc 1 200 -d .- | nrev | nleet | napp -c '@#$' > dict1.txt
```
The above, with just 4 keywords in `words.txt` (one of which was numerical), generated a wordlist of 2279744 passwords (38MB).

As demonstrated, much like Unix utilities, the tools of Narthex can be thought of as building blocks, where the user has all the power to connect them in different possible ways to generate the desired list of passwords.

## Donate
[![paypal](https://mcdim.xyz/media/button_paypal2.png)](https://www.paypal.com/donate/?hosted_button_id=HZXXLD586P5CW)

More donation options on the website: <a href="https://mcdim.xyz/"/>mcdim.xyz</a>
