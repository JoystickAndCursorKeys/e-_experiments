0 turbo
30 cl$ ="0123456789abcdef"
100 print chr$ (147)
105 cw=9: bx = 8: x = bx: y = 1
110 r$ ="{right}": d$="{down}": for t=1 to 7:r$=r$+r$: d$=d$+d$:next
120 print "{white}{clear}";:ly = 0
125 for c = 0to 255:yo =y *40:o =yo +x
130 poke 1024+o ,c :poke 55296+o , 1
135 x =x + 1:lx =lx + 1
140 if lx = 4then x =x + cw
145 if lx = 8then x =x + cw
150 remif lx =12then x =x + cw
155 if lx =12then x = bx:lx = 0:y =y + 1
160 next
165 o = 0:for zy = 1to 22
170 for zx = 1to 35step (cw+4)
175 gosub 200:z0=o:gosub 1130 : hx$=z$: 
176 z=o: gosub 1200: 
177 if o<256 then print hx$; "/"; z$ :o =o + 4
180 next
185 next
190 goto 190
195 rem- cursor zx,zy
200 z$ =d$
205 z1$ =left$(z$ ,zy)
210 z$ =r$
215 z1$ =z1$ +left$(z$ , zx)
220 print "{home}";chr$ (154);z1$ ;
225 return
1130 rem- z$ = tohex( z0 )
1137 z1=z0
1140 zr$ ="":z2 =4096
1145 zn =int (z1 /z2 )
1150 if zn >15then print "error": end
1155 zn$ =mid$ (cl$ ,zn + 1, 1)
1160 if zn > 0or zr$ <>""then zr$ =zr$; zn$
1165 z1 =z1 -(zn *z2 )
1170 z2 =z2 /16
1175 if z2 < 1then goto 1185
1180 goto 1145
1185 z$ = "0"
1190 if zr$ <>""then z$= zr$
1194 if len(z$)=1 then z$ = "0";z$
1195 return
1200 rem- z$ = pad3( z )
1210 z$=str$(z):z$=right$(z$,len(z$)-1)
1220 if len(z$)<3 then z$=" ";z$
1225 if len(z$)<3 then z$=" ";z$
1230 return
