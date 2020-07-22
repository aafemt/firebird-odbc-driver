# firebird-odbc-driver

Firebird ODBC driver

## Differences from the official version
- Catalogue functions follow ODBC specifications and unconditionally return NULL as catalogue and schema name. Query text isn't altered in this regard anymore.
- SQLTables() supports "GLOBAL TEMPORARY" table type.
- Data types returned by SQLTypeInfo() made more consistent to fix MS Power BI warning about non-searcheable field if varchar is used as PK.
- Custom attributes SQL_FBGETPAGEDB, SQL_FBGETWALDB and SQL_FBGETSTATINFODB are disabled as conflicting with ODBC 4 specifications.
