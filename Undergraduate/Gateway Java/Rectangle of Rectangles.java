import java.util.Scanner; 
import java.io.PrintWriter; 
import java.io.IOException; 
import java.io.FileInputStream; 
import java.awt.Color;

/**
 * EN.500.112 Gateway Computing: Java, Project 4.
 * Creates a checkerboard, snake, and diagonal pattern based on input.
 * Melissa Martinez D4E3E5 mmart213
 * March 28, 2023
 */ 
public class Project4 {
     
   public static void main(String[] args) throws IOException {
      
      Scanner scnr = new Scanner(System.in);
      
      //Checkerboard
      System.out.print("Enter Checkerboard size: ");
      int gridSize = scnr.nextInt();
      
      System.out.print("Enter RGB values, each [0,255]: ");
      int rVal = scnr.nextInt();
      int gVal = scnr.nextInt();
      int bVal = scnr.nextInt();
      
      String checkName = "checkerboard" + gridSize + ".txt";
      PrintWriter outfile = new PrintWriter(checkName);
      outfile.println(gridSize + " " + gridSize);
      
      StdDraw.setPenColor(StdDraw.LIGHT_GRAY);
      StdDraw.filledRectangle(0.5, 0.5, 0.5, 0.5);
      checkerboard(gridSize, rVal, gVal, bVal, outfile);
      outfile.flush();
      outfile.close();
      
      //Snake
      System.out.print("Enter Snake input filename: ");
      String snakeName = scnr.next();
      FileInputStream fileSnake = new FileInputStream(snakeName);
      Scanner inS = new Scanner(fileSnake);
      
      StdDraw.setPenColor(StdDraw.LIGHT_GRAY);
      StdDraw.filledRectangle(0.5, 0.5, 0.5, 0.5);
      snake(inS);
      
      //Diagonal
      System.out.print("Enter Diagonals input filename: ");
      String diagName = scnr.next(); 
      FileInputStream fileDiag = new FileInputStream(diagName);
      Scanner inD = new Scanner(fileDiag);
      
      StdDraw.setPenColor(StdDraw.LIGHT_GRAY);
      StdDraw.filledRectangle(0.5, 0.5, 0.5, 0.5);
      diagonal(inD);
      
      fileSnake.close();
      fileDiag.close();
   }
   
   /**
    * Creates diagonal pattern.
    * @param scnr Scanner that reads from file to present diagonal
    */ 
   public static void diagonal(Scanner scnr) {
      
      int rows = scnr.nextInt();
      int cols = scnr.nextInt();
      if (rows != cols) {
         System.out.println("Specified pattern is not square so cannot" +
            " be displayed by Diagonals operation.");
      }
      else {
         Rectangle[][] grid = new Rectangle[rows][cols];
         String data = "";
         scnr.nextLine();
      
         for (int r = 0; r < rows; r++) {
         
            for (int c = 0; c < cols; c++) {
            
               data = scnr.nextLine();
               grid[r][c] = new Rectangle(data);
            
            }
         }
         
         for (int i = 0; i < rows; i++) {
         
            for (int j = 0; j < rows; j++) {
               
               if (i == 0) {
                  grid[j][j].draw();
                  StdDraw.pause(200);
               }
               
               else {
                  if (i + j < rows) {
                     grid[j][j + i].draw();
                     StdDraw.pause(200);
                  }
               }
               
            }
            
            for (int j = 0; j < rows; j++) {
               
               if (i != 0) {
                  if (i + j < rows) {
                     grid[i + j][j].draw();
                     StdDraw.pause(200);
                  }
               }
               
            }
         }
      }
   }
   
   /**
    * Creates snake pattern.
    * @param scnr Scanner that reads from file to present snake 
    */ 
   public static void snake(Scanner scnr) {
   
      int rows = scnr.nextInt();
      int cols = scnr.nextInt();
      Rectangle[][] grid = new Rectangle[rows][cols];
      String data = "";
      scnr.nextLine();
      
      for (int r = 0; r < rows; r++) {
         
         for (int c = 0; c < cols; c++) {
            
            data = scnr.nextLine();
            grid[r][c] = new Rectangle(data);
            
         }
      }
      
      for (int c = 0; c < cols; c++) {
         
         for (int r = 0; r < rows; r++) {
            
            if (c % 2 == 0) {
               grid[r][c].draw();
               StdDraw.pause(200);
            }
            else {
               grid[rows - r - 1][c].draw();
               StdDraw.pause(200);
            }
         }
      }
      
   }
   
   /**
    * Creates checkerboard pattern.
    * @param gridSize How many rows and columns in output
    * @param red Red value in RGB
    * @param green Green value in RGB
    * @param blue Blue value in RGB
    * @param outfile Where rectangle information will be output
    */ 
   public static void checkerboard(int gridSize, int red, int green, 
      int blue, PrintWriter outfile) {
      
      Rectangle[][] grid = new Rectangle[gridSize][gridSize];
      Color squareColor = new Color(red, green, blue);
      Color squareWhite = new Color(255, 255, 255);
      double sqDim = 1.0 / gridSize;
      double xCenter = sqDim / 2;
      double yCenter = sqDim / 2;
      
      for (int r = 0; r < gridSize; r++) {
         
         for (int c = 0; c < gridSize; c++) {
            
            if ((r + c) % 2 == 0) {
               grid[r][c] = new Rectangle(squareWhite, sqDim, sqDim, true,
               (c * sqDim) + xCenter, 1 - ((r * sqDim) + yCenter));
               
               //draw the current rectangle on the screen  
               grid[r][c].draw();
               StdDraw.pause(200);

               //write the current rectangle's info into the output file
               outfile.println(grid[r][c].toString());
            }
            else {
               grid[r][c] = new Rectangle(squareColor, sqDim, sqDim, true,
               (c * sqDim) + xCenter, 1 - ((r * sqDim) + yCenter));
               
               //draw the current rectangle on the screen  
               grid[r][c].draw();
               StdDraw.pause(200);

               //write the current rectangle's info into the output file
               outfile.println(grid[r][c]);
            }
         }
      }
   }
   
}
