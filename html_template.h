#ifndef HTML_TEMPLATE_H_INCLUDED
#define HTML_TEMPLATE_H_INCLUDED
#include <cstring>
const int SIZ = 2048;

const char *ok_response =
    "HTTP/1.0 200 OK\n"
    "Content-type: text/html\n"
    "\n";

const char *page_start =
    "<html>\n"
    "<head>\n"
    "<title>server_copyright@wsl1999</title>\n"
    "<style>\n"
    ".center\n"
    "{\n"
    "text-align: center;\n"
    "border: 3px solid black;\n"
    "}\n"
    "</style>\n"
    "</head>\n"
    "<body>\n"
    "<div class="
    "center"
    ">"
    "\n<h1>WEB SERVER Ver 1.0</h1>\n"
    "<p>\n";

const char *page_end =
    "\n</p>\n"
    "</div>\n"
    "</body>\n"
    "<br/>"
    "<h3>Click <a href="
    "/"
    ">HERE</a> to return.</h3>\n"
    "<br/>"
    "<p>Copyright @Wang Shuailong 2017012265</p>"
    "<p>Department of Physics.</p>"
    "<p><em>Tsinghua Univetsity</em></p>"
    "</html>\n";

const char *not_found_response =
    "HTTP/1.0 404 Not Found\n"
    "Content-type: text/html\n"
    "\n"
    "<html>\n"
    "<body>\n"
    "<h1>404 Not Found</h1>\n"
    "<p>The requested URL was not found on this server.</p>\n"
    "</body>\n"
    "</html>\n"; //404 error.

void Generate_html(char *text, char *buf_module)
{
    strcat(text, ok_response);
    strcat(text, page_start);
    strcat(text, buf_module);
    strcat(text, page_end);
}

void Buf_HTML_Table(char *buf, char *text, int filelength)
{
    strcat(text, "\n<table><tr><td>\n");
    for (int i = 0; i < filelength - 1; i++)
    {
        if (buf[i] == 32)
        {
            strcat(text, "\n</td><td>\n");
            while (buf[i] == 32 && buf[i + 1] == 32)
            {
                i++;
            }
        }
        else if (buf[i] == '\n' && buf[i + 1] == '\0')
        {
            strcat(text, "\n</td></tr></table>\n");
        }
        else if (buf[i] == '\n' && buf[i + 1] != '\0')
        {
            strcat(text, "\n</td></tr><tr><td>\n");
        }
        else
        {
            int k = 0;
            while (text[k] != '\0')
            {
                k++;
            }
            text[k] = buf[i];
        }
    }
}

#endif // HTML_TEMPLATE_H_INCLUDED
