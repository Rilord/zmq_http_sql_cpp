import sqlite3
import random
import string

ID_LEN = 1
VALUE_MAX = 10

def get_random_id(n : int) -> str:
    return ''.join(random.choice(string.ascii_uppercase + string.digits) for _ in range(n))


def get_random_val() -> int:
    return random.randint(0, VALUE_MAX)

def gen_random(len: int) -> list:
    return [(get_random_id(ID_LEN), get_random_val()) for _ in range(len)]


def gen_table(filename: str, name: str, len: int):
    con = sqlite3.connect(filename)

    cur = con.cursor()
    cur.execute("create table {0} (id text, value real)".format(name))

    data = gen_random(len)

    for row in data:
        cur.execute("insert into {0} values ('{1}',{2})".format(name, row[0], row[1]))

    con.commit()
    con.close()

def gen_table_3(filename: str, table1: str, table2: str, table3: str):
    con = sqlite3.connect(filename)

    cur = con.cursor()

    cur.execute("""insert into {0} (id, value)
select {1}.id, {1}.value
  from {1}
       left join {2}
         on {1}.id = {2}.id
        and {1}.value = {2}.value
union all
select {2}.id, {2}.value
  from {2}
 where not exists (select null
                     from {1}
                    where {2}.id = {1}.id
                      and {2}.value = {1}.value)""".format(table3, table1, table2));

    con.commit()
    con.close()


gen_table("task.db", "table1", 50)
gen_table("task.db", "table2", 50)
gen_table("task.db", "table3", 0)

gen_table_3("task.db", "table1", "table2", "table3")
