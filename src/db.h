#ifndef DB_H
#define DB_H

#include <stdint.h>
#include "input.h"
#include <stdbool.h>

#define COLUMN_USERNAME_SIZE 32
#define COLUMN_EMAIL_SIZE 255
#define TABLE_MAX_PAGES 100
#define size_of_attribute(Struct, Attribute) sizeof(((Struct *)0)->Attribute)

typedef struct
{
    uint32_t id;
    char username[33];
    char email[256];
} Row;

typedef enum
{
    META_COMMAND_SUCCESS,
    META_COMMAND_UNRECOGNIZED_COMMAND
} MetaCommandResult;

typedef enum
{
    PREPARE_SUCCESS,
    PREPARE_NEGATIVE_ID,
    PREPARE_STRING_TOO_LONG,
    PREPARE_SYNTAX_ERROR,
    PREPARE_UNRECOGNIZED_STATEMENT
} PrepareResult;

typedef enum
{
    EXECUTE_SUCCESS,
    EXECUTE_TABLE_FULL,
    EXECUTE_DUPLICATE_KEY
} ExecuteResult;

typedef enum
{
    STATEMENT_INSERT,
    STATEMENT_SELECT
} StatementType;

typedef struct
{
    StatementType type;
    Row row_to_insert;
} Statement;

typedef struct
{
    int file_descriptor;
    uint32_t file_length;
    uint32_t num_pages;
    void *pages[TABLE_MAX_PAGES];
} Pager;

typedef struct
{
    uint32_t root_page_num;
    Pager *pager;
} Table;

typedef struct
{
    Table *table;
    uint32_t page_num;
    uint32_t cell_num;
    bool end_of_table;
} Cursor;

typedef enum
{
    NODE_INTERNAL,
    NODE_LEAF
} NodeType;

Table *db_open(const char *filename);
void db_close(Table *table);
MetaCommandResult do_meta_command(InputBuffer *input_buffer, Table *table);
PrepareResult prepare_statement(InputBuffer *input_buffer, Statement *statement);
ExecuteResult execute_statement(Statement *statement, Table *table);
Cursor *table_start(Table *table);
Cursor *table_end(Table *table);
void cursor_advance(Cursor *cursor);
uint32_t* leaf_node_num_cells(void* node);
void* leaf_node_cell(void* node, uint32_t cell_num);
uint32_t* leaf_node_key(void* node, uint32_t cell_num);
void* leaf_node_value(void* node, uint32_t cell_num);
void initialize_leaf_node(void* node);
void *get_page(Pager *pager, uint32_t page_num);
void serialize_row(Row *source, void *destination);
NodeType get_node_type(void *node);
Cursor *table_find(Table *table, uint32_t key);
void set_node_type(void *node, NodeType type);
Cursor *leaf_node_find(Table *table, uint32_t page_num, uint32_t key);

#endif
