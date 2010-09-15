f = File.open("actor_centrality_degrees.txt", "r")
array = []
f.each_line do |l|
	array << [l.split(" ")[0].to_f, l.split(" ")[1]]
end
array.sort! {|x,y| y[0] <=> x[0]}

f = File.open("ordered_actor_centrality_degrees.txt", "w")
array.each do |el|
   f << el[0] << "\t" << el[1]  << "\n"
end


f = File.open("actor_betweenness.txt", "r")
array = []
f.each_line do |l|
	array << [l.split(" ")[0].to_f, l.split(" ")[1]]
end
array.sort! {|x,y| y[0] <=> x[0]}


f = File.open("ordered_actor_betweenness.txt", "w")

array.each do |el|
   f << el[0] << "\t" << el[1] << "\n"
end