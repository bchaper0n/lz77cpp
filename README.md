# [lz77](https://en.wikipedia.org/wiki/LZ77_and_LZ78) implementation in c++

lossless data compression algorithm by Abraham Lempel and Jacob Ziv in 1977

## implementation steps
1. suffix array (sorting using quick sort for now; [SA-IS](https://www.zork.net/~st/jottings/sais.html) todo)
   - also convert to/from suffix tree?
2. sliding window + dictionary
3. encoder
4. decoder

## future
- implement [lzss](https://en.wikipedia.org/wiki/Lempel%E2%80%93Ziv%E2%80%93Storer%E2%80%93Szymanski)
- implement [huffman coding](https://en.wikipedia.org/wiki/Huffman_coding)
- implement [DEFLATE](https://en.wikipedia.org/wiki/Deflate)
