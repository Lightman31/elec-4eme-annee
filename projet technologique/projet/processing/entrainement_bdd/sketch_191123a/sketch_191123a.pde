


Table table;

void setup() {

  int i = 0;
  table = loadTable("ING4_uid_main.csv", "header");
  
  println(table.getRowCount() + " total rows in table");
  int table_presence[] = new int [20];
  long table_id[] = new long [20];
  long table_NE[] = new long [20];
  String table_prenom[] = new String [20];
  String table_nom[] = new String [20];
  for (TableRow row : table.rows()) {

    int id1 = row.getInt("id1");
    int id2 = row.getInt("id2");
    long id = id1*100000000L + id2;
    String species = row.getString("Nom");
    String name = row.getString("Prenom");
    long numE = row.getInt("NumEtudiant");
    table_id[i] = id;
    table_NE[i] = numE;
    table_prenom[i] = name;
    table_nom[i] = species;
    table_presence[i] = 0;

    println(name + " (" + species + ") has an ID of " + id + "num Etudiant : " + numE);
    i = i+1;
  }

}
