/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
 *                                 Technische Informatik II                                      *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                                                                                               *
 *                                    C G A _ S C R E E N                                        *
 *                                                                                               *
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#ifndef __screen_include__
#define __screen_include__

/* INCLUDES */

#include <machine/io_port.h>

/* CLASSES */

/** \brief CGA-Dispaly driver
 *
 * CGA_Screen enables the basic control of the screen of a computer by accessing
 * the screen memory and I/O ports directly.
 */
class CGA_Screen {
  private:
     
    /**
     * 
     */
    struct ScreenChar{
      char c;
      unsigned char attrib;
    };
    
    
    /**
     * 
     */
    enum Ports{
      indexPortNum=0x3d4, 
      dataPortNum=0x3d5,
      memoryBase=0xb8000
    };
    
    /**
     * 
     */
    enum Constants{
      COLUMNS=80,
      ROWS=25
    };
    
    ScreenChar (*screen)[COLUMNS];
    IO_Port index_port;
    IO_Port data_port;

  protected:
    /** 
     * \~german
     * \brief Attribut, welches genommen wird, wenn sonst nichts spezifiziert ist
     * 
     * Diese aktuellen Standardattribute werden von den meisten Funktionen dieser Klasse 
     * beim Setzen der CGA-Attribute genutzt.
     * 
     * \~english
     * \brief default attribute if no other is defined
     */
    unsigned char attribute;

  public:
    
    /** 
     * \brief Constructor
     */
    CGA_Screen();
    
    /** 
     * \brief Destructor 
     */
    ~CGA_Screen();
    
    /** \brief set the cursor position
     *
     * @param x column number of new position 
     * @param y row number of new position
     */
    void setpos(unsigned short x, unsigned short y);
    
    /** \brief get the cursor position
     *
     * @param x reference for column number of current position
     * @param y reference for row number of curent position
     */
    void getpos(unsigned short& x, unsigned short& y) const;
    
    /** \brief print a character to a specific position
     *
     * @param x column number of display position
     * @param y row number of display position
     * @param c character to be displayed
     * @param attrib display attributs
     */
    void show(unsigned short x, unsigned short y, char c, unsigned char attrib);
    
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
