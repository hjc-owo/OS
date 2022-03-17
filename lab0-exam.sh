make
touch hello_os
mkdir hello_os_dir
cp os_hello ./hello_os_dir
mv ./hello_os_dir/os_hello ./hello_os_dir/hello_os
cp os_hello ./hello_os_dir
rm os_hello

grep -in os_hello hello_os.c > hello_os.txt
