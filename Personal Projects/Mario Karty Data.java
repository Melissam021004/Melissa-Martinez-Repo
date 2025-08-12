import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.util.Scanner;
import java.io.PrintWriter;

/**
 * Making a quick program to see who texts the most in our fam groupchat
 */
public class CarDataAnalysis {

   // column index constants for car data file
   static final int BRAND = 2;
   static final int YEAR = 4;
   static final int MILEAGE = 6;
   static final int PRICE = 1;
   static final int DATE = 0;

   /**
    * Counts the number of lines in a given plain-text file.
    * @param filename The file whose lines are to be counted.
    * @return the number of lines in the file.
    * @throws IOException
    */
   public static int countFileLines(String filename)
                                    throws IOException {

      FileInputStream fileByteStream = new FileInputStream(filename);
      Scanner line = new Scanner(fileByteStream);
      int out = 0;
      while (line.hasNextLine()) {
         line.nextLine();
         out++;
      }
      return out;

   }

   
   /**
    * Loads integer data from source into columns.
    * @param column Column in which data is stored
    * @param loc Location of data of interest in original data
    * @param filename Name of data file
    * @return Array with data of interest
    */
   public static int[] intColumnLoader(int[] column, int loc, String filename) 
      throws IOException {
      FileInputStream fileByteStream = new FileInputStream(filename);
      Scanner inFS = new Scanner(fileByteStream);
      String[] line = new String[13];
      String headers = inFS.nextLine();
      for (int i = 0; i < column.length; i++) {
         line = (inFS.nextLine()).split(",");
         column[i] = Integer.parseInt(line[loc]);
      }
      return column;
   }
   
   
   /**
    * Loads string data from source into columns.
    * @param column Column in which data is stored
    * @param loc Location of data of interest in original data
    * @param filename Name of data file
    * @return Array with data of interest
    */
   public static String[] stringColumnLoader(String[] column, 
      int loc, String filename) throws IOException {
      FileInputStream fileByteStream = new FileInputStream(filename);
      Scanner inFS = new Scanner(fileByteStream);
      String[] line = new String[13];
      String headers = inFS.nextLine();
      for (int i = 0; i < column.length; i++) {
         line = (inFS.nextLine()).split(",");
         column[i] = line[loc];
      }
      return column;
   }
   
   }
   

   /**
    * Drive the Car Data Analysis program.
    * @param args This program does not take commandline arguments.
    * @throws IOException
    */
   public static void main(String[] args) throws IOException {

      // output purpose
      System.out.println("Hi we are here to figure out who the best fam members are");

      // get input filename
      System.out.print("Please enter input filename: ");
      Scanner keyboard = new Scanner(System.in);
      String filename = keyboard.nextLine();

      // count the number of rows in the file (ignore headers line)
      int rowCount = countFileLines(filename);

      //declare and allocate parallel arrays for each column of interest
      FileInputStream fileByteStream = new FileInputStream(filename);
      Scanner inFS = new Scanner(fileByteStream);
      
      int[] date = new int[rowCount];
      int[] price = new int[rowCount];
      double[] mileage = new double[rowCount];
      int[] year = new int[rowCount];
      String[] brand = new String[rowCount];
      
      //load columns from file
      date = intColumnLoader(num, DATE, filename);
      // price = intColumnLoader(price, PRICE, filename);
      // year = intColumnLoader(year, YEAR, filename);
      // mileage = doubleColumnLoader(mileage, MILEAGE, filename);
      // brand = stringColumnLoader(brand, BRAND, filename);
      

   }

}
