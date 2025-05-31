#ifndef QUERY_BUILDER_H
#define QUERY_BUILDER_H

#include <string>
#include <vector>
#include <map>

/**
 * @class QueryBuilder
 * @brief Helper class for building CSV queries
 *
 * This class provides utility methods for building and executing
 * query-like operations on CSV files. It simplifies the process
 * of selecting, filtering, and manipulating data in CSV format.
 */
class QueryBuilder
{
private:
    std::string _tableName;                              ///< Name of the CSV file (without extension)
    std::vector<std::string> _selectedColumns;           ///< Columns to return in results
    std::map<std::string, std::string> _whereConditions; ///< Filtering conditions

public:
    /**
     * @brief Constructor that initializes with a table name
     * @param tableName Name of the CSV file (without extension)
     */
    QueryBuilder(const std::string &tableName);

    /**
     * @brief Select specific columns for the query
     * @param columns Vector of column names to select
     * @return Reference to this QueryBuilder for method chaining
     */
    QueryBuilder &select(const std::vector<std::string> &columns);

    /**
     * @brief Add a WHERE condition to filter results
     * @param column Column name to filter on
     * @param value Value to compare against
     * @return Reference to this QueryBuilder for method chaining
     */
    QueryBuilder &where(const std::string &column, const std::string &value);

    /**
     * @brief Generate a CSV file path from the table name
     * @return Full filename with .csv extension
     */
    std::string getFileName() const;

    /**
     * @brief Get the selected columns
     * @return Vector of column names
     */
    const std::vector<std::string> &getSelectedColumns() const;

    /**
     * @brief Get the WHERE conditions
     * @return Map of column-value pairs for filtering
     */
    const std::map<std::string, std::string> &getWhereConditions() const;
};

#endif // QUERY_BUILDER_H