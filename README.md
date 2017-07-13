![Templus Logo](/images/logo.png)

Templus is a commandline tool for generating static webpages.

## About Templus
Templus takes **posts** contained in text files and inserts them into an html document as a blog style layout.
A **post manifest** (default: manifest.txt) determines the order in which the posts are added to the page.
A **tags file** (default: tags.txt) stores the html tags that will wrap each post and each posts title, byline, and content.
A **template file** (default: template.html) contains the html page that will be used to generate the static  webpage.

## Building Templus
Templus can be built with your favorite C/C++ compiler.

### Example with g++
```
g++ -o Templus.out
```

This will build Templus and create an executable called Templus.out.

## Usage
Templus has two commands
* new
* gen

### New
new is used to create a new post and add it to the manifest.
#### Example
```
./Templus.out new bobs-new-post.txt
```

This will create a new post named bobs-new-post.txt and populate it with an example post.  bobs-new-post.txt is then also added to the manifest.  If bobs-new-post.txt is already in the manifest then the file will not be created.

### Gen
gen is used to generate a static blog page.
#### Example 1
```
./Templus.out gen
```

This will generate a static webpage using the default files.
#### Example 2
```
./Templus.out gen my-template.html
```

This will generate a static webpage using my-template.html as the template file and the result will be stored in the default output file gen.html.
#### Example 3
```
./Templus.out gen my-template.html my-site.html
```

This will generate a static webpage using my-template.html as the template file and my-site.html will be the output result of the generation.
#### Example 4
```
./Templus.out gen -c config.txt
```

This will generate a static page according to the configuration specified in config.txt.

## Creating a Templus Configuration File
A Templus configuration file can contain four peices of information.

* Location/name of the template file
* Location/name of the output file
* Location/name of the manifest file
* Location/name of the tags file

Templus uses directives to identify this information.  There are four configuration directives.

* :template:
* :output:
* :manifest:
* :tags:

### Example Configuration File
```
:template:
my-template.html

:output:
index.html

:manifest:
my-manifest.txt

:tags:
my-tags.txt
```

## Creating a Template
A template is a normal html file for the most part.  To turn an html file into a Templus template, add **{:t:}**  on it's own line where you want the blog posts to appear.  Make sure that there is no indentation infront of the **{:t:}**.  It must be at the beginning of the line and it must be the only thing on the line.
### Example Template

```html
<html>
    <head>
        <title>T E M P L U S</title>
    </head>
    <body>
        <h1>
            Hello World!
        </h1>
{:t:}
        <h3>
            Goodbye!
        </h3>

    </body>
</html>
```

## Creating a Templus Tags File
The default html tags that will surround the title, byline, and content of each post as well as each post itself is defined in tags.txt.
A custom tags file can be created and used instead of the deafualt tags.txt.
Opening and closing tags have to be on their own lines.
### Example

```html
:title:
<h1>
</h1>

:byline:
<h2>
</h2>

:content:
<div><p>
</p></div>

:post:
<div>
</div>
```