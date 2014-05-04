/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
 *                                 Technische Informatik II                                      *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                                                                                               *
 *                                       M E M O R Y                                             *
 *                                                                                               *
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#ifndef __mem_include__
#define __mem_include__

#define FLAG_AMOUNT 1024 * 1024
#define MEMORY_SIZE FLAG_AMOUNT * 8

static volatile unsigned char _heap[MEMORY_SIZE];
static volatile unsigned char _flags[FLAG_AMOUNT];

/**
 * @brief The Memory class
 *
 * Allocates a large amount of memory as a "heap" to work with.
 * Provides memalloc-functionalities.
 */
class Memory {
private:

  static bool initialized;

  /**
   * @brief isByteReserved
   * @param pos
   * @return whether the byte at position is reserved
   */
  static bool isByteReserved(int pos);

  /**
   * @brief isReserved
   * @param start the beginning of the segment
   * @param size the size
   * @return returns whether the area is reserved or not
   */
  static bool isReserved(int start, int size);

  /**
   * @brief doReserve
   * @param start the beginning of the segment
   * @param size the requested size
   */
  static void doReserve(int start, int size);

  /**
   * @brief doReserve
   * @param start the beginning of the segment
   * @param size the requested size
   * @param free whether to reserve or free
   */
  static void doReserve(int start, int size, bool free);

public:

  /**
   * @brief initialize the memory
   */
  static void initialize();

  /**
   * @brief allocates requested amount of memory
   * @param size the requested size
   * @return a pointer to the memory-segment
   */
  static void* alloc(int size);

  /**
   * @brief frees the area in memory
   * @param mem the pointer
   * @param size the size
   */
  static void free(void* mem, int size);

  /**
   * @brief allocatedMemory
   * @return returns the total amount of memory reserved
   */
  static int allocatedMemory();

  /**
   * @brief availableMemory
   * @return returns the size of biggest coherent chunk of free memory space
   */
  static int availableMemory();

  /**
   * @brief totalAvailableMemory
   * @return returns the total amount of memory avaible
   */
  static int totalAvailableMemory();

};

#endif
