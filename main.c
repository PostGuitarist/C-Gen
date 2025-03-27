#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_BUFFER_SIZE 1024

// Basic function to convert markdown to HTML
char* markdown_to_html(const char* markdown_text) {
    char* html_text = (char*)malloc(MAX_BUFFER_SIZE * sizeof(char));

    if (html_text == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return NULL;
    }

    strcpy(html_text, markdown_text);

    return html_text;
}

// Generate HTML file from markdown content and template
void generate_html(const char* input_filename, const char* output_filename) {
    FILE *input_file = fopen(input_filename, "r");
    if (input_file == NULL) {
        fprintf(stderr, "Could not open input file: %s\n", input_filename);
        return;
    }

    FILE *output_file = fopen(output_filename, "w");
    if (output_file == NULL) {
        fprintf(stderr, "Could not open output file: %s\n", output_filename);
        fclose(input_file);
        return;
    }

    const char* html_template_start = "<!DOCTYPE html>\n<html>\n<head>\n<title>Markdown to HTML</title>\n</head>\n<body>\n";
    const char* html_template_end = "\n</body>\n</html>";

    char title[MAX_BUFFER_SIZE];

    strncpy(title, input_filename, strlen(input_filename) - 3);
    title[strlen(input_filename) - 3] = '\0';

    fprintf(output_file, html_template_start, title);

    char line[MAX_BUFFER_SIZE];
    while (fgets(line, MAX_BUFFER_SIZE, input_file) != NULL) {
        char* html_line = markdown_to_html(line);
        fprintf(output_file, "<p>%s</p>\n", html_line);
        free(html_line);
    }

    fprintf(output_file, "%s", html_template_end);
    fclose(input_file);
    fclose(output_file);
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <input_markdown_file>\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char* input_filename = argv[1];
    char output_filename[MAX_BUFFER_SIZE];

    strcpy(output_filename, input_filename);
    
    // Change the file extension from .md to .html
    output_filename[strlen(output_filename) - 2] = 'h';
    output_filename[strlen(output_filename) - 1] = 't';
    output_filename[strlen(output_filename)] = 'm';
    output_filename[strlen(output_filename) + 1] = 'l';
    output_filename[strlen(output_filename) + 2] = '\0';

    generate_html(input_filename, output_filename);

    printf("HTML file generated: %s\n", output_filename);

    return EXIT_SUCCESS;
}