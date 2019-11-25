


Table table;

void setup() {

  table = loadTable("ING4_uid_main.csv", "header");

  println(table.getRowCount() + " total rows in table");

  for (TableRow row : table.rows()) {

    int id1 = row.getInt("id1");
    int id2 = row.getInt("id2");
    long id = id1*100000000L + id2;
    String species = row.getString("Nom");
    String name = row.getString("Prenom");

    println(name + " (" + species + ") has an ID of " + id1 + id2);
    println(name + " (" + species + ") has an ID of " + id);
  }

}
