/**
 * Project 5A
 * TestCard class checks the methods in Card class.
 * Melissa Martinez D4E3E5 April 13, 2023
 */
public class TestCard {

   public static void main(String[] args) {
   
      Card a = new Card(2, 4);
      Card b = new Card(1, 4);
      Card c = new Card(1, 4);
      Card d = new Card(2, 2);
      Card e = new Card(14, 14);
      Card kingOfClubs = new Card(13, 1);
      
      assertEquals(1, a.compareTo(b), "Cards are correctly compared.");
      assertEquals(-1, b.compareTo(a), "Cards are correctly compared.");
      assertEquals(0, b.compareTo(c), "Cards are correctly compared.");
      assertEquals(1, a.compareTo(d), "Cards are correctly compared.");
      
      System.out.println(a); //Should print "2 of Spades"
      System.out.println(b); //Should print "Ace of Spades"
      System.out.println(e); //Should print "Invalid card"
      System.out.println(kingOfClubs); //Should print "King of Clubs"
      
      if (b.equals(c)) {
         System.out.println("PASS: Cards are correctly assigned as equal.");
      }
      else {
         System.out.println("FAIL: equals class does not work.");
      }
      
      assertEquals(13, kingOfClubs.getRank(), "Rank is correctly assigned.");
      assertEquals(1, kingOfClubs.getSuit(), "Suit is correctly assigned.");
      assertEquals(0, e.getRank(), "Rank is correctly assigned.");
      assertEquals(0, e.getSuit(), "Suit is correctly assigned.");
   }
   
  /**
   * A helper method to assert that two integers are equal.
   * @param exp expected integer value.
   * @param act actual integer value.
   * @param dsc description of the test.
   */
   public static void assertEquals(int exp, int act, String dsc) {
      if (exp == act) {
         System.out.println("PASS: " + dsc);
      } else {
         System.out.println("FAIL: " + dsc);
      }
   }
   
}