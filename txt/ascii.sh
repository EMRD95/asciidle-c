printf "Do you want to add Pinups to the txt folder? Yes or no? (y/n) "
read response

if [ "$response" = "y" ]; then
for i in {00..48}
do
  wget -O pinups$i.txt https://asciipr0n.com/pr0n/pinups/pinup$i.txt
done
fi
