#include <stdio.h>
#include <sqlite3.h>
#include <assert.h>

static int callback(void *_user_data, int argc, char **argv, char **_col_names) {
  assert (argc == 1);
  assert (argv[0][0] == '1');
  return 0;
}

int main(int argc, char **argv){
  fprintf(stderr, "[INFO] esy-sqlite-test: Running a basic SQL test...\n");
  sqlite3 *db;
  char *zErrMsg = 0;
  int rc;

  rc = sqlite3_open(":memory:", &db);

  if (rc) {
    fprintf(stderr,
        "[ERROR] esy-sqlite-test: Can't open database: %s\n",
        sqlite3_errmsg(db)
    );
    sqlite3_close(db);
    return(1);
  }

  rc = sqlite3_exec(db, "SELECT 1", callback, 0, &zErrMsg);
  if (rc != SQLITE_OK) {
    fprintf(stderr, "[ERROR] esy-sqlite-test: %s\n", zErrMsg);
    sqlite3_free(zErrMsg);
  }

  sqlite3_close(db);
  fprintf(stderr, "[INFO] esy-sqlite-test: OK\n");

  return 0;
}

