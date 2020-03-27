#include <stdio.h>
#include <sqlite3.h>
#include <assert.h>

static int callback(void *_user_data, int argc, char **argv, char **_col_names) {
  assert (argc == 1);
  assert (argv[0] == "1");
  return 0;
}

int main(int argc, char **argv){
  sqlite3 *db;
  char *zErrMsg = 0;
  int rc;

  rc = sqlite3_open(":memory:", &db);

  if (rc) {
    fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
    sqlite3_close(db);
    return(1);
  }

  rc = sqlite3_exec(db, "SELECT 1", callback, 0, &zErrMsg);
  if (rc != SQLITE_OK) {
    fprintf(stderr, "SQL error: %s\n", zErrMsg);
    sqlite3_free(zErrMsg);
  }

  sqlite3_close(db);
  return 0;
}

