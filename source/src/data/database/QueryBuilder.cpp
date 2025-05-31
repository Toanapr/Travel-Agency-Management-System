#include "QueryBuilder.h"

QueryBuilder::QueryBuilder(const std::string &tableName) : _tableName(tableName)
{
}

QueryBuilder &QueryBuilder::select(const std::vector<std::string> &columns)
{
    _selectedColumns = columns;
    return *this;
}

QueryBuilder &QueryBuilder::where(const std::string &column, const std::string &value)
{
    _whereConditions[column] = value;
    return *this;
}

std::string QueryBuilder::getFileName() const
{
    return _tableName + ".csv";
}

const std::vector<std::string> &QueryBuilder::getSelectedColumns() const
{
    return _selectedColumns;
}

const std::map<std::string, std::string> &QueryBuilder::getWhereConditions() const
{
    return _whereConditions;
}