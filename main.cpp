#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

int main(int argc, char *argv[]) {

    ifstream infile;
    ifstream infile_post;
    ifstream infile_manifest;
    ifstream infile_tags;
    ifstream infile_template;

    ofstream outfile;
    ofstream outfile_gen;

    string buffer = "";
    string buffer_manifest = "";
    string buffer_template = "";
    string buffer_post = "";

    bool post_exists = false;
    bool errors = false;
    std::string post_name = "";

    // needed files
    string manifest = "manifest.txt";
    string tags = "tags.txt";
    string template_file = "template.html";

    // default generated file
    string generated_file = "gen.html";

    // optional file
    string config_file = "";

    // command line argument containers
    string arg1;
    string arg2;
    string arg3;

    // possible commands
    string new_post = "new";
    string gen = "gen";
    string gen_config = "-c";

    // tags strings
    string title_tag_open = "";
    string title_tag_close = "";
    string byline_tag_open = "";
    string byline_tag_close = "";
    string content_tag_open = "";
    string content_tag_close = "";
    string post_tag_open = "";
    string post_tag_close = "";

    // tag directives
    string title_directive = ":title:";
    string byline_directive = ":byline:";
    string content_directive = ":content:";
    string post_directive = ":post:";

    // template directive // this is used inside the html template
    string template_directive = "{:t:}";

    // config directives
    string template_config_directive = ":template:";
    string output_config_directive = ":output:";
    string manifest_config_directive = ":manifest:";
    string tags_config_directive = ":tags:";

    // convert command line arguments to strings
    switch(argc)
    {
        case 1:
            break;
        case 2:
            arg1 = argv[1];
            break;
        case 3:
            arg1 = argv[1];
            arg2 = argv[2];
            break;
        case 4:
            arg1 = argv[1];
            arg2 = argv[2];
            arg3 = argv[3];
        default:
            break;
    }


    // parse command line args
    if(arg1 == new_post)
    {
        // check for argv[1]
        if(argc == 3)
        {
            // check if filename is in manifest
            post_name = arg2;
            post_exists = false;
            infile.open(manifest);
            while(!infile.eof() && !post_exists)
            {
                getline(infile, buffer);
                if(post_name == buffer)
                {
                    post_exists = true;
                }
            }
            if(post_exists)
            {
                infile.close();
                cout << "A post file with this name already exists." << endl;
            }
            else
            {
                // create file
                // add new file name to manifest
                infile.close();
                outfile.open(manifest, ofstream::out | ofstream::app);
                outfile << post_name << endl;
                outfile.close();
                outfile.open(post_name);
                outfile.close();

                // post template
                outfile.open(post_name, ofstream::out | ofstream::app);
                // title
                outfile << ":title:" << endl;
                outfile << "Example Post" << endl;
                outfile << ":title:" << endl << endl;

                // post
                outfile << ":byline:" << endl;
                outfile << "Example byline" << endl;
                outfile << ":byline:" << endl << endl;

                // content
                outfile << ":content:" << endl;
                outfile << "Example content.  Lorem ipsum dolor sit amet, consectetur adipiscing elit. "
                        << "Etiam lacinia pretium nulla, ut fermentum risus porttitor sit amet. "
                        << "Nam in nibh augue. Fusce posuere hendrerit magna et cursus. Sed efficitur "
                        << "a nisi non auctor. Donec mattis neque a augue aliquet, "
                        << "eu malesuada tellus dignissim. In et metus nibh." << endl;
                outfile << ":content:" << endl << endl;
            }
        }
        else
        {
            cout << "Error: Invalid parameters" << endl;
        }
    }
    else if(arg1 == gen)
    {
        // generate page
        if(argc == 3)
        {
            template_file = arg2;
        }
        if(argc == 4)
        {

            if(arg2 == gen_config)
            {
                config_file = arg3;
                infile.open(config_file);
                if(infile.fail())
                {
                    cout << "Error: Could not open configuration file" << endl;
                    errors = true;
                }
                else
                {
                    // load from configuration
                    while(!infile.eof())
                    {
                        getline(infile, buffer);
                        if(buffer == template_config_directive)
                        {
                            getline(infile, buffer);
                            template_file = buffer;
                        }
                        if(buffer == output_config_directive)
                        {
                            getline(infile, buffer);
                            generated_file = buffer;
                        }
                        if(buffer == manifest_config_directive)
                        {
                            getline(infile, buffer);
                            manifest = buffer;
                        }
                        if(buffer == tags_config_directive)
                        {
                            getline(infile, buffer);
                            tags = buffer;
                        }
                    }
                }
                infile.close();
            }
            else
            {
                template_file = arg2;
                generated_file = arg3;
            }
        }

        if(!errors)
        {
            //========================//
            // read tags //

            infile.open(tags);

            if(infile.fail())
            {
                cout << tags << " not found" << endl;
            }
            else
            {
                while(!infile.eof())
                {
                    getline(infile, buffer);
                    if(buffer == title_directive)
                    {
                        getline(infile, buffer);
                        title_tag_open = buffer;
                        getline(infile, buffer);
                        title_tag_close = buffer;
                    }
                    else if(buffer == byline_directive)
                    {
                        getline(infile, buffer);
                        byline_tag_open = buffer;
                        getline(infile, buffer);
                        byline_tag_close = buffer;
                    }
                    else if(buffer == content_directive)
                    {
                        getline(infile, buffer);
                        content_tag_open = buffer;
                        getline(infile, buffer);
                        content_tag_close = buffer;
                    }
                    else if(buffer == post_directive)
                    {
                        getline(infile, buffer);
                        post_tag_open = buffer;
                        getline(infile, buffer);
                        post_tag_close = buffer;
                    }
                }
            }
            //========================//

            infile_manifest.open(manifest);
            infile_template.open(template_file);
            if(infile_manifest.fail() || infile_template.fail())
            {
                cout << "Error: One or more crucial files could not be opened" << endl;
            }
            else
            {
                outfile_gen.open(generated_file, fstream::trunc);
                while(!infile_template.eof())
                {
                    getline(infile_template,buffer_template);
                    if(buffer_template == template_directive)
                    {
                        outfile_gen << post_tag_open << endl;
                        while(!infile_manifest.eof())
                        {
                            getline(infile_manifest, buffer_manifest);
                            infile_post.open(buffer_manifest);
                            if(infile_post.fail() && buffer_manifest != "")
                            {
                                cout << "Error: Could not open " << buffer_manifest << endl;
                                infile_post.close();
                            }
                            else
                            {
                                while(!infile_post.eof())
                                {
                                    getline(infile_post, buffer_post);
                                    if(buffer_post == title_directive)
                                    {
                                        outfile_gen << title_tag_open << endl;
                                        do
                                        {
                                            getline(infile_post,buffer_post);
                                            if(buffer_post != title_directive)
                                            {
                                                outfile_gen << buffer_post << endl;
                                            }
                                        }while(buffer_post != title_directive && !infile_post.eof());
                                    }
                                    else if(buffer_post == byline_directive)
                                    {
                                        outfile_gen << byline_tag_open << endl;
                                        do
                                        {
                                            getline(infile_post,buffer_post);
                                            if(buffer_post != byline_directive)
                                            {
                                                outfile_gen << buffer_post << endl;
                                            }
                                        }while(buffer_post != byline_directive && !infile_post.eof());
                                    }
                                    else if(buffer_post == content_directive)
                                    {
                                        outfile_gen << content_tag_open << endl;
                                        do
                                        {
                                            getline(infile_post,buffer_post);
                                            if(buffer_post != content_directive)
                                            {
                                                outfile_gen << buffer_post << endl;
                                            }
                                        }while(buffer_post != content_directive && !infile_post.eof());
                                    }
                                }
                                infile_post.close();
                            }
                        }
                        outfile_gen << post_tag_close << endl;
                    }
                    else
                    {
                        outfile_gen << buffer_template << endl;
                    }
                }
            }
            infile_manifest.close();
            infile_template.close();
        }
    }
    return 0;
}