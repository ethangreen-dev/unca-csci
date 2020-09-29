
void phase_6(char *input)
{
  int *input_nums_ptr;
  int **int_array;
  undefined1 *puVar1;
  int iVar2;
  long memory_iter;
  int iVar4;
  int *piVar5;
  int input_nums[6];
  int local_60[2];
  int *ptr_array[6];

  piVar5 = input_nums;
  input_nums_ptr = input_nums;
  
  // Make sure we have 6 numbers in the input array.
  read_six_numbers(input, (long)input_nums);

  iVar4 = 0;

  // Iterate down the array making sure that each value is unique.
  // If a given value exists more than once in the array, blow the bomb up.
  while (true)
  {
    // Check to make sure the first element of input_nums - 1 is greater than 5.
    if (5 < *piVar5 - 1U)
    {
      explode_bomb();
    }

    iVar4 = iVar4 + 1;
    iVar2 = iVar4;

    // Possible break condition here.
    if (iVar4 == 6) 
    {
      break;
    }

    // This inner loop iterates down each index in the array, comparing it to the element pointed at 
    // by piVar5. 
    // If there is a match, the bomb explodes.
    do
    {
      // If *pivar5 equals the element at index iVar2 in the array, explode the bomb.
      if (*piVar5 == input_nums[iVar2])
      {
        explode_bomb();
      }

      iVar2 = iVar2 + 1;
    } while (iVar2 < 6);

    piVar5 = piVar5 + 1;
  }

  // Iterate through the indices subtracting each from 7.
  // This loop will subtract each number in the input_nums array from 7.
  do
  {
    *input_nums_ptr = 7 - *input_nums_ptr;
    input_nums_ptr = input_nums_ptr + 1;
  } while (input_nums_ptr != local_60);
  // The above statement stops when the current input_nums_ptr is equal to local_60, which follows input_nums in memory.

  memory_iter = 0;

  do
  {
    // If the value at index memory_iter is less than 2, set puVat1 to node1. 
    // node1 doesn't seem to be doing anything.
    
    // After some thought, maybe this node is a struct. Not sure.
    if (*(int *)((long)input_nums + memory_iter) < 2)
    {
      puVar1 = node1;
    }

    // If the value at index memory_iter is 2 or greater.
    else
    {
      iVar4 = 1;
      puVar1 = node1;

      // 
      do
      {
        // Step the puVar1 pointer 2 * n bytes. 
        puVar1 = *(undefined1 **)((int *)puVar1 + 2);
        
        // Increment iVar4 by one.
        iVar4 = iVar4 + 1;

        // Loop while iVar4 does not equal the memory_iter index in the input_nums array.
      } while (iVar4 != *(int *)((long)input_nums + memory_iter));
    }

    // Set the value at index memory_iter * 2 in the pointer array ptr_array to puVar1.
    // All this is doing is setting (memory_iter / 8)'s to puVar1. 
    // Remember. Pointer math works around factors of that datatype. In this instance, we are casting ptr_array to a long and then
    // adding onto it. 
    *(undefined1 **)((long)ptr_array + memory_iter * 2) = puVar1;
    
    // Increment memory_iter by 4. Possibly something of note here -- maybe a 4 byte datatype?
    memory_iter = memory_iter + 4;

    // Continue iterating while memory_iter does not equal 0x18 (24 in d);
    // It seems as though we're again iterating down each value in the array.
    // memory_iter is stepping down an offset from input_nums in memory, 6 times (0 -> 24). 
  } while (memory_iter != 0x18);

  // Set the new int_array var to the second entry in the ptr_array.
  int_array = ptr_array[1];
  
  // Set the input_nums_array to the first entry in the ptr_array.
  input_nums_ptr = ptr_array[0];

  do
  {
    piVar5 = int_array[0];
    *(int **)(input_nums_ptr + 2) = piVar5;
    int_array = int_array + 1;
    input_nums_ptr = piVar5;

  } while (int_array != (int **)&stack0xffffffffffffffd8);

  *(char **)(piVar5 + 2) = 0;
  iVar4 = 5;

  do
  {
    if (*ptr_array[0] < **(int **)(ptr_array[0] + 2))
    {
      explode_bomb();
    }

    ptr_array[0] = *(int **)(ptr_array[0] + 2);
    iVar4 = iVar4 + -1;
  } while (iVar4 != 0);

  return;
}
