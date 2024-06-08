#ifndef DB_H
#define DB_H

#include <stdint.h>
#include "input.h"
#include <stdbool.h>

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
    EXECUTE_TABLE_FULL
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
    void *pages[100];
} Pager;

typedef struct
{
    uint32_t num_rows;
    Pager *pager;
} Table;

typedef struct {
    Table *table;
    uint32_t row_num;
    bool end_of_table;
} Cursor;

Table *db_open(const char *filename);
void db_close(Table *table);
MetaCommandResult do_meta_command(InputBuffer *input_buffer, Table *table);
PrepareResult prepare_statement(InputBuffer *input_buffer, Statement *statement);
ExecuteResult execute_statement(Statement *statement, Table *table);
Cursor *table_start(Table *table);
Cursor *table_end(Table *table);
void cursor_advance(Cursor* cursor);

#endif
