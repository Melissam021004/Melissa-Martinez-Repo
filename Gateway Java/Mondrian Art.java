import java.util.Scanner;

/**Project A, EN.500.112 Gateway Computing: Java.
*Class creates variation of Mondrian art depending on given measurements
*Melissa Martinez D4E3E5
*Due February 3rd, 2023
*/
public class Project1 {

   public static void main(String[] args) {

      Scanner kb = new Scanner(System.in);
      
      double blueWidth; 
      double blueHeight;
      double topLeftHeight;
      double bottomRightWidth;
      
      System.out.print("Enter percent for blue block width: ");
      blueWidth = kb.nextDouble() / 100;
      
      System.out.print("Enter percent for blue block height: ");
      blueHeight = kb.nextDouble() / 100;
      
      System.out.print("Enter percent for top left block height: ");
      topLeftHeight = kb.nextDouble() / 100;
      
      System.out.print("Enter percent for bottom right block width: ");
      bottomRightWidth = kb.nextDouble() / 100;
      
      //Lower left blue block
      StdDraw.setPenColor(StdDraw.BLUE);
      StdDraw.filledRectangle(blueWidth / 2, blueHeight / 2, blueWidth / 2, 
         blueHeight / 2);
      
      //Yellow Rectangle
      StdDraw.setPenColor(StdDraw.YELLOW);
      StdDraw.filledRectangle(1 - bottomRightWidth / 2, blueHeight / 4, 
         bottomRightWidth / 2, blueHeight / 4);
      
      //Right Vertical Line
      StdDraw.setPenRadius(0.02);
      StdDraw.setPenColor();
      StdDraw.line(1 - bottomRightWidth, 0, 1 - bottomRightWidth, blueHeight);
      
      //Mini Horizontal Line on Bottom Right Corner
      StdDraw.setPenRadius(0.02);
      StdDraw.setPenColor();
      StdDraw.line(1 - bottomRightWidth, blueHeight / 2, 1, blueHeight / 2);
      
      //Red rectangle
      StdDraw.setPenColor(StdDraw.RED);
      StdDraw.filledRectangle((1 - blueWidth) / 2 + blueWidth, (1 - blueHeight)
         / 2 + blueHeight, (1 - blueWidth) / 2, (1 - blueHeight) / 2);
      
      //Bottom Horizontal Line
      StdDraw.setPenRadius(0.01);
      StdDraw.setPenColor();
      StdDraw.line(0, blueHeight, 1, blueHeight);
      
      //Circle
      StdDraw.setPenColor(StdDraw.WHITE);
      StdDraw.filledCircle(blueWidth, 1 - topLeftHeight, topLeftHeight / 3);
      
      StdDraw.setPenColor(StdDraw.BLUE);
      StdDraw.arc(blueWidth, 1 - topLeftHeight, topLeftHeight / 3, 90, 180);
      
      StdDraw.setPenColor(StdDraw.YELLOW);
      StdDraw.arc(blueWidth, 1 - topLeftHeight, topLeftHeight / 3, 180, 270);
      
      StdDraw.setPenColor();
      StdDraw.arc(blueWidth, 1 - topLeftHeight, topLeftHeight / 3, 270, 90);
      
      //Left Vertical Line
      StdDraw.setPenRadius(0.01);
      StdDraw.setPenColor();
      StdDraw.line(blueWidth, 0, blueWidth, 1);
      
      //Top Horizontal Line
      StdDraw.setPenRadius(0.03);
      StdDraw.setPenColor();
      StdDraw.filledRectangle(blueWidth / 2, 1 - topLeftHeight,
         blueWidth / 2, 0.03 / 2);
      
   }
}
