
n = ARGV[0].to_i

n.times { |i|
puts "Generating file ##{i}"
f = File.open "gr#{i}.gen.gr", "w+" 
vn = ["A"]
vt = []
p = {}
s = "A"

vn_size = (rand() * 10).to_i
vt_size = (rand() * 10).to_i

(1..vn_size).each do |x| vn << ('A'.bytes.first + x).chr end
(0..vt_size - 1).each do |x| vt << ('a'.bytes.first + x).chr end

(0..(rand() * 8).to_i).each do |x|
	i = (rand() * vn.size).to_i
	j = (rand() * vt.size).to_i
	list = (p[vn[i]]) ? p[vn[i]] : []
	type = (rand() * 4).to_i
	list << "#{vn[i]}#{vt[j]}" if type == 0
	list << vt[j] if type == 1
	list << "\\" if type == 2
	list << "#{vt[i]}#{vn[j]}" if type == 3 || type > 3	
	p[vn[i]] = list
end

f.print "G1 = ({"
vn.each_with_index do |x,i| 
	f.print x
	f.print "," unless i == vn.size - 1
end
f.print "},{"
vt.each_with_index do |x,i| 
	f.print x
	f.print "," unless i == vt.size - 1
end
f.print "},"
f.print s
f.print ",{"
p.keys.each_with_index do |prod, index|
	_p = p[prod]
	f.print prod
	f.print "->"
	_p.each_with_index do |tkn, i|
		f.print tkn
		f.print "|" unless i == _p.size - 1
	end
	f.print "," unless index == p.keys.size - 1
end
f.puts "})"
f.close
}
