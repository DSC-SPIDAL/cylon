/*
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef TWISTERX_SRC_IO_TABLE_API_H_
#define TWISTERX_SRC_IO_TABLE_API_H_

#include <string>
#include <vector>
#include <functional>
#include "status.hpp"
#include "join/join_config.h"
#include "io/csv_read_config.h"
#include "io/csv_write_config.h"
#include "ctx/twisterx_context.h"
#include "row.hpp"

/**
 * This file shouldn't have an arrow dependency. Use the table_api_extended to define
 * the functions with arrow dependency
 */
namespace twisterx {

void RemoveTable(const std::string &id);

twisterx::Status ReadCSV(twisterx::TwisterXContext *ctx,
                         const std::string &path,
                         const std::string &id,
                         twisterx::io::config::CSVReadOptions options = twisterx::io::config::CSVReadOptions());

twisterx::Status ReadCSV(twisterx::TwisterXContext *ctx,
                         const std::vector<std::string> &paths,
                         const std::vector<std::string> &ids,
                         twisterx::io::config::CSVReadOptions options);

twisterx::Status WriteCSV(const std::string &id, const std::string &path,
                          const twisterx::io::config::CSVWriteOptions& options = twisterx::io::config::CSVWriteOptions());

twisterx::Status JoinTables(twisterx::TwisterXContext *ctx,
                            const std::string &table_left,
                            const std::string &table_right,
                            twisterx::join::config::JoinConfig join_config,
                            const std::string &dest_id);

twisterx::Status DistributedJoinTables(
    twisterx::TwisterXContext *ctx,
    const std::string &table_left,
    const std::string &table_right,
    twisterx::join::config::JoinConfig join_config,
    const std::string &dest_id
);

twisterx::Status Union(twisterx::TwisterXContext *ctx,
                       const std::string &table_left,
                       const std::string &table_right,
                       const std::string &dest_id);

twisterx::Status DistributedUnion(
    twisterx::TwisterXContext *ctx,
    const std::string &table_left,
    const std::string &table_right,
    const std::string &dest_id
);

int ColumnCount(const std::string &id);

int64_t RowCount(const std::string &id);

/**
 * Print a table
 * @param table_id id of the table
 * @param col1
 * @param col2
 * @param row1
 * @param row2
 * @return
 */
twisterx::Status Print(const std::string &table_id, int col1, int col2, int row1, int row2);

twisterx::Status PrintToOStream(const std::string &table_id,
                                int col1,
                                int col2,
                                int row1,
                                int row2,
                                std::ostream &out,
                                char delimiter = ',',
                                bool use_custom_header = false,
                                const std::vector<std::string> &headers = {});

/**
 * Merge the set of tables into a single table, each table should have the same schema
 *
 * @param table_ids ids of the tables
 * @param merged_tab id of the merged table
 * @return the status of the merge
 */
twisterx::Status Merge(twisterx::TwisterXContext *ctx,
                       std::vector<std::string> table_ids,
                       const std::string &merged_tab);

/**
 * Sort the table with the given identifier
 * @param id table id
 * @param columnIndex the sorting column index
 * @return the status of the merge
 */
twisterx::Status SortTable(twisterx::TwisterXContext *ctx,
                           const std::string &tableId,
                           const std::string &sortTableId,
                           int columnIndex);

/**
 * Partition the table into multiple tables using a hash function, hash will be applied to the bytes of the data
 * @param id the table id
 * @param hash_columns the hash columns, at the moment we only use the first column
 * @param no_of_partitions number of partitions to output
 * @param out tables created after hashing
 * @param pool the memory pool
 * @return the status of the partition operation
 */
twisterx::Status HashPartition(twisterx::TwisterXContext *ctx,
                               const std::string &id,
                               const std::vector<int> &hash_columns,
                               int no_of_partitions,
                               std::unordered_map<int, std::string> *out);

/**
 * Select a set of rows based on the selector condition
 *
 * @param id id the table id
 * @param selector row selection logic
 * @return the status of the partition operation
 */
Status Select(twisterx::TwisterXContext *ctx,
              const std::string &id,
              const std::function<bool(twisterx::Row)> &selector,
              const std::string &out);

Status Project(const std::string &id, const std::vector<int64_t>& project_columns, const std::string &out);
}
#endif //TWISTERX_SRC_IO_TABLE_API_H_
