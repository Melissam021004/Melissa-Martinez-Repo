import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.util.Scanner;
import java.io.PrintWriter;

/**
 * Car Data Analysis: Project 3 Starter Code.
 * Returns a variety of data/calculations from a car dataset
 * Melissa Martinez D4E3E5
 * Gateway Programming: Java
 * Johns Hopkins University
 * Spring 2023
 */
public class CarDataAnalysis {

   // menu options
   static final int BRAND_QUERY = 1;
   static final int TWO_HIGHEST_PRICES_QUERY = 2;
   static final int RANGE_QUERY = 3;
   static final int BEST_VALUE_QUERY = 4;
   static final int QUIT = 5;

   // column index constants for car data file
   static final int BRAND = 2;
   static final int YEAR = 4;
   static final int MILEAGE = 6;
   static final int PRICE = 1;
   static final int NUM = 0;

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
    * Print the program menu to the console.
    */
   public static void printMenu() {

      System.out.printf("[%d]: Average price of brand.\n", BRAND_QUERY);
      System.out.printf("[%d]: Two highest prices.\n",
             TWO_HIGHEST_PRICES_QUERY);
      System.out.printf("[%d]: Average price in year and mileage range.\n",
             RANGE_QUERY);
      System.out.printf("[%d]: Best value.\n", BEST_VALUE_QUERY);
      System.out.printf("[%d]: Quit.\n", QUIT);
      System.out.print("Please select an option: ");

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
    * Loads double data from source into columns.
    * @param column Column in which data is stored
    * @param loc Location of data of interest in original data
    * @param filename Name of data file
    * @return Array with data of interest
    */
   public static double[] doubleColumnLoader(double[] column, 
      int loc, String filename) throws IOException {
      FileInputStream fileByteStream = new FileInputStream(filename);
      Scanner inFS = new Scanner(fileByteStream);
      String[] line = new String[13];
      String headers = inFS.nextLine();
      for (int i = 0; i < column.length; i++) {
         line = (inFS.nextLine()).split(",");
         column[i] = Double.parseDouble(line[loc]);
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
   
   /**
    * Prints matching entries with average price of cars in that brand.
    * @param rowCount Number of rows in the entire dataset.
    * @param brandArray Array of all brands in entire set.
    * @param price Array of prices of all cars in set.
    * @param mileage Array of mileage of all cars in set.
    * @param year Array of manufacturing year of all cars in set.
    * @param keyboard Scanner item.
    */
   public static void brandQuery(int rowCount, String[] brandArray, 
      int[] price, double[] mileage, int[] year, Scanner keyboard)
      throws IOException {
      
      System.out.print("Please enter a car brand: ");
      String brandIn = keyboard.next();
      
      System.out.print("Please enter an output filename: ");
      String outfile = keyboard.next();
      
      FileOutputStream fileOutStream = new FileOutputStream(outfile);
      PrintWriter outFS = new PrintWriter(fileOutStream);
      
      double pricetot = 0;
      int counter = 0;
      
      for (int i = 0; i < rowCount; i++) {
         if ((brandArray[i]).equals(brandIn.toLowerCase())) {
            pricetot += price[i];
            counter++;
            outFS.println(i + ", " + brandIn + ", " + year[i] + ", " 
               + mileage[i] + ", " + price[i]);
         }
      
      }
      
      if (counter == 0) {
         System.out.print("There are no matching entries for brand " +
            brandIn + ".");
      }
      else {
         System.out.printf("There are " + counter +  
            " matching entries for brand Ford with an average price of %.2f.",
            pricetot / counter);
      }
      
      System.out.println();
      outFS.flush();
      fileOutStream.close();
   }
   
   /**
    * Method that returns two highest prices in data set.
    * @param prices Array of all prices in data set
    */
   public static void twoHighest(int[] prices) {
      int price1 = prices[0];
      int price2 = prices[1];
      int rows = prices.length;
      for (int i = 2; i < rows; i++) {
         if (prices[i] > price1 && prices[i] > price2) {
            if (price1 > price2) {
               price2 = prices[i];
            }
            
            else {
               price1 = prices[i];
            }
         }
         
         else if (prices[i] > price1) {
            price1 = prices[i];
         }
         
         else if (prices[i] > price2) {
            price2 = prices[i];
         }
      }
      if (price1 > price2) {
         System.out.println("The two highest prices are $" + price1 +
            ".00 and $" + price2 + ".00.");
      }
      else {
         System.out.println("The two highest prices are $" + price2 +
            ".00 and $" + price1 + ".00.");
      }
   }
   
   /**
    * Method that takes in year/mileage range and prints the 
    * number of matches and their average price.
    * @param year Array of manufacturing year of the cars
    * @param mileage Array of car mileage of the cars
    * @param price Array of prices of cars in dataset
    * @param scnr Scanner for user input
    */
   public static void rangeQuery(int[] year, double[] mileage, 
      int[] price, Scanner scnr) {
      
      int counter = 0;
      double priceTot = 0;
      int rows = year.length;
      
      System.out.print("Please enter the year lower bound: ");
      int yearLower = scnr.nextInt();
      
      System.out.print("Please enter the year upper bound: ");
      int yearUpper = scnr.nextInt();
      
      System.out.print("Please enter the mileage lower bound: ");
      int miLower = scnr.nextInt();
      
      System.out.print("Please enter the mileage upper bound: ");
      int miUpper = scnr.nextInt();
      
      for (int i = 0; i < rows; i++) {
         if (year[i] >= yearLower && year[i] <= yearUpper &&
            mileage[i] >= miLower && mileage[i] <= miUpper) {
            
            counter++;
            priceTot += price[i];
         }
      }
      
      System.out.printf("There are " + counter +
         " matching entries for year range [" + yearLower + 
         ", " + yearUpper + "] and mileage range [" +
         miLower + ", " + miUpper + "] with an average price of $%.2f.\n",
         priceTot / counter);
      
   }
   
   /**
    * Method that takes in year/mileage range and prints the 
    * car with best value within range with formula.
    * @param year Array of manufacturing year of the cars
    * @param mileage Array of car mileage of the cars
    * @param price Array of prices of cars in dataset
    * @param brand Array of the car brands in dataset
    * @param scnr Scanner for user input
    */
   public static void bestVal(int[] year, double[] mileage, 
      int[] price, String[] brand, Scanner scnr) {
      
      int bestIndex = 0;
      double currVal = 0;
      double bestVal = 0;
      int len = year.length;
      
      System.out.print("Please enter lower mileage threshold: ");
      int miLower = scnr.nextInt();
      
      System.out.print("Please enter lower price threshold: ");
      int priceLower = scnr.nextInt();
      
      for (int i = 0; i < len; i++) {
         if (price[i] > priceLower && mileage[i] > miLower) {
            currVal = year[i] - mileage[i] / 13500 - price[i] / 1900.0;
            if (currVal > bestVal) {
               bestVal = currVal;
               bestIndex = i;
            }
         }
      }
      
      System.out.println("The best-value entry with more than " +
         miLower + ".0 miles and a price higher than $" + priceLower +
         " is a " + year[bestIndex] + " " + brand[bestIndex] +
         " with " + mileage[bestIndex] + " miles for a price of $"
         + price[bestIndex] + ".");
   }

   /**
    * Drive the Car Data Analysis program.
    * @param args This program does not take commandline arguments.
    * @throws IOException
    */
   public static void main(String[] args) throws IOException {

      // output purpose
      System.out.println("Welcome to the car dataset analysis program.");

      // get input filename (e.g. "USA_cars_datasets.csv")
      System.out.print("Please enter input csv filename: ");
      Scanner keyboard = new Scanner(System.in);
      String filename = keyboard.nextLine();

      // count the number of rows in the file (ignore headers line)
      int rowCount = countFileLines(filename) - 1;
      System.out.println("File has " + rowCount + " entries.");
      System.out.println();

      //declare and allocate parallel arrays for each column of interest
      FileInputStream fileByteStream = new FileInputStream(filename);
      Scanner inFS = new Scanner(fileByteStream);
      
      int[] num = new int[rowCount];
      int[] price = new int[rowCount];
      double[] mileage = new double[rowCount];
      int[] year = new int[rowCount];
      String[] brand = new String[rowCount];
      
      //load columns from file
      num = intColumnLoader(num, NUM, filename);
      price = intColumnLoader(price, PRICE, filename);
      year = intColumnLoader(year, YEAR, filename);
      mileage = doubleColumnLoader(mileage, MILEAGE, filename);
      brand = stringColumnLoader(brand, BRAND, filename);
      

      // while the user doesn't choose to quit...
      int option = 0;
      while (option != QUIT) {

         // display the menu and get an option
         printMenu();
         option = keyboard.nextInt();

         switch (option) {
            case BRAND_QUERY:
               brandQuery(rowCount, brand, price, mileage, year, keyboard);
               break;
            case TWO_HIGHEST_PRICES_QUERY:
               twoHighest(price);
               break;
            case RANGE_QUERY:
               rangeQuery(year, mileage, price, keyboard);
               break;
            case BEST_VALUE_QUERY:
               bestVal(year, mileage, price, brand, keyboard);
               break;
            case QUIT:
               System.out.println("Thank you for using the program!");
               break;
            default:
               System.out.println("Invalid option.");

         }

         // leave empty line for next printing of menu
         System.out.println();

      }

   }

}
