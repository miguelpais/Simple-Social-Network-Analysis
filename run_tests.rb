file = %x[ls out]
if file == ""
   puts "Executable not found. Run make first"
else
   %x[cp ./out "system tests/Fiorentine Families"]
   lol = %x[cd "system tests/Fiorentine Families";./out 1 -u]
   test1 = %x[diff "system tests/Fiorentine Families/actor_centrality_degrees.txt" "system tests/Fiorentine Families/correct_actor_centrality_degrees.txt"]
   if test1 != ""
      puts "01. FAILED: Actor Degree Centrality Test"
      puts test1
   else
      puts "01. PASSED: Actor Degree Centrality Test"
   end

   test2 = %x[diff "system tests/Fiorentine Families/group_centrality_degree.txt" "system tests/Fiorentine Families/correct_group_centrality_degree.txt"]
   if test2 != ""
      puts "02. FAILED: Group Degree Centrality Test"
      puts test2
   else
      puts "02. PASSED: Group Degree Centrality Test"
   end

   test3 = %x[diff "system tests/Fiorentine Families/actor_betweenness.txt" "system tests/Fiorentine Families/correct_actor_betweenness.txt"]
   if test3 != ""
      puts "03. FAILED: Actor Betweenness Test"
      puts test3
   else
      puts "03. PASSED: Actor Betweenness Test"
   end

   test4 = %x[diff "system tests/Fiorentine Families/group_betweenness.txt" "system tests/Fiorentine Families/correct_group_betweenness.txt"]
   if test4 != ""
      puts "04. FAILED: Group Betweenness Test"
      puts test4
   else
      puts "04. PASSED: Group Betweenness Test"
   end
   
   test5 = %x[diff "system tests/Fiorentine Families/properties.txt" "system tests/Fiorentine Families/correct_properties.txt"]
   if test5 != ""
      puts "05. FAILED: Properties Test"
      puts test5
   else
      puts "05. PASSED: Properties Test"
   end

   puts "Removing moved and generated files..."
   %x[rm "system tests/Fiorentine Families/group_betweenness.txt"]
   %x[rm "system tests/Fiorentine Families/actor_betweenness.txt"]
   %x[rm "system tests/Fiorentine Families/group_centrality_degree.txt"]
   %x[rm "system tests/Fiorentine Families/actor_centrality_degrees.txt"]
   %x[rm "system tests/Fiorentine Families/properties.txt"]
   %x[rm "system tests/Fiorentine Families/out"]
   puts "OK"

end