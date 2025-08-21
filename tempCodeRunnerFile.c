non_repeating_char(struct LQueue *queue)
// {
//     if (isEmpty(queue))
//     {
//         printf("Queue is empty!\n");
//         return -1;
//     }

//     int freq[1000] = {0};  // adjust size based on max value possible

//     // First pass: count frequencies
//     for (int i = queue->front; i <= queue->rear; i++)
//     {
//         freq[queue->arr[i]]++;
//     }

//     // Second pass: find first element with frequency = 1
//     for (int i = queue->front; i <= queue->rear; i++)
//     {
//         if (freq[queue->arr[i]] == 1)
//         {
//             return queue->arr[i];
//         }
//     }

//     return -1; // No non-repeating element
// }
