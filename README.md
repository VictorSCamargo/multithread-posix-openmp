# multithread posix openmp
 
## Run

Using unix type OS with `bash`, do `chmod +x run.sh` to give permitions to the script and run the file. `./run.sh`.

### Possible problems

Depending on input values, sementation faults can happen.

## Notes and tips

Those notes are for the testers and developers.

### Notes

Big number of arrays with low number of elements tends to be a lot better to singlethread algorythms.

Big number of elements per array tends to be better to multithread but can cause segmentation faults because of the size.

Each new array has a bigger cost for creating the threads in the multithread algorithms than singlethread ones.