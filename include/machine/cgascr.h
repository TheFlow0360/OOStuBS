/*
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
 *                                 Technische Informatik II                                      *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                                                                                               *
 *                                    C G A _ S C R E E N                                        *
 *                                                                                               *
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#ifndef __screen_include__
#define __screen_include__

/* INCLUDES */

/* CLASSES */

/** \brief CGA-Dispaly driver
 *
 * CGA_Screen enables the basic control of the screen of a computer by accessing
 * the screen memory and I/O ports directly.
 */
class CGA_Screen {
  private:

  // some constants

#define MEMORY_START 0xB8000
#define CHARS_PER_ROW 80
#define ROW_COUNT 25

  // Cursor stuff

#define INDEX_REG 0x3d4
#define DATA_REG  0x3d5
#define CURSOR_LOW 15
#define CURSOR_HIGH 14

  // Attribute stuff

  /**
   * @brief The CGA_AttrByte struct
   *
   * Maps the Attributes on one byte
   */
  struct CGA_AttrByte {
    unsigned
    fgColor: 4,
    bgColor: 3,
    blink: 1;
  };

  /**
   * @brief The CGA_Attr union
   */
  union CGA_Attr {
    char byte;
    CGA_AttrByte set;
  };

  /**
   * @brief The CGA_Char struct
   *
   * The two bytes representing a char in the screen buffer.
   */
  struct CGA_Char {
    char character;
    CGA_Attr attr;
  };

  /**
   * @brief active attribute
   */
  CGA_Attr attr;

  /**
   * @brief compute the address to write to
   * @param x Line
   * @param y Position
   * @return Address
   */
  inline int computeAddress(unsigned short x, unsigned short y)
  {
    return MEMORY_START + 2 * CHARS_PER_ROW * x + 2 * y;
  }

 public:
    
    /** 
     * \brief Constructor
     *
     * Sets up memory mapping of CGA driver, sets default attribute for output and cleares the screen.
     */
    CGA_Screen();
    
    /** 
     * \brief Destructor 
     *
     * Prints a warning that the os ended.
     */
    ~CGA_Screen();
    
    /** \brief set the cursor position
     *
     * @param x column number of new position 
     * @param y row number of new position
     */
    void setpos(unsigned short y, unsigned short x);
    
    /** \brief get the cursor position
     *
     * @param x reference for column number of current position
     * @param y reference for row number of curent position
     */
    void getpos(unsigned short& y, unsigned short& x) const;
    
    /** \brief print a character to a specific position
     *
     * @param x column number of display position
     * @param y row number of display position
     * @param character character to be displayed
     * @param attribute display attributs
     */
    void show(unsigned short x, unsigned short y, char character, unsigned char attrib);
    
    /**
     * @brief print a character to a specific position
     *
     * @param x column number of display position
     * @param y row number of display position
     * @param c a CGA-Char represntation of the Character
     */
    void show(unsigned short x, unsigned short y, CGA_Char c);

    /** 
     * \~german
     * \brief gibt eine Zeichenkette an der aktuellen Position aus
     * 
     * Als Attribute werden die hinterlegten, aktuellen, Standardwerte verwendet.
     * 
     * @param string 
     *    Zeichenkette, die ausgegeben werden soll
     * @param n 
     *    Anzahl an Zeichen, die von \c string ausgegeben werden soll
     * 
     * 
     * \~english
     * \brief print a string to the current position
     * 
     * @param string 
     *    string of characters to be displayed
     * @param n 
     *    number auf characters in string
     */
    void print(const char* string, unsigned int n);

    /**
     * \~german
     * \brief gibt eine Zeichenkette an der aktuellen Position aus
     *
     * Als Attribute werden die hinterlegten, aktuellen, Standardwerte verwendet.
     *
     * @param string
     *    Zeichenkette, die ausgegeben werden soll
     *
     *
     * \~english
     * \brief print a string to the current position
     *
     * @param string
     *    string of characters to be displayed
     */
    void print(const char* string);
    
    /** 
     * \~german
     * \brief das aktuelle Display wird eine Zeile nach oben gescrollt
     *
     * Die so entstandene neue Zeile wird mit Leertasten aufgefüllt.
     * Die Attribute dafür sind die aktuellen Standardwerte.
     * 
     * \~english
     * \brief scroll the display one line upwards
     *
     * The new row at the bottom of the screen is filled with spaces. The default 
     * attributes are use.
     */
    void scrollup();
    
    /** 
     * \~german
     * \brief leert den aktuellen Bildschirm
     * 
     * Dabei werden alle Zeilen mit Leertasten gefüllt. Als Attribute werden die 
     * in einer Variable hinterlegten, aktuellen Standardwerte verwendet.
     * 
     * \~english
     * \brief clear the screen 
     */
    void clear();
    
    /** 
     * \~german
     * \brief ändert die aktuellen Standardattribute
     * 
     * Diese aktuellen Standardattribute werden von den meisten Funktionen dieser Klasse 
     * beim Setzen der CGA-Attribute genutzt.
     * 
     * \param fgColor
     *    Vordergrundfarbe
     * 
     * \param bgColor
     *    Hintergrundfarbe
     * 
     * \param blink
     *    Soll der Text blinken? (true=blinken)
     * 
     * \~english
     * \brief changes the used default attribute values 
     * 
     * Most of the function uses these attribute values to determine which values the new printed
     * text should have.
     * 
     * \param fgColor
     *    foregorund color
     * 
     * \param bgColor
     *    backgorund color
     * 
     * \param blink
     *    indecates if the text should blink (true = should blink)
     */
    void setAttributes(int fgColor, int bgColor, bool blink);
};

#endif
