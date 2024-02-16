let SessionLoad = 1
let s:so_save = &g:so | let s:siso_save = &g:siso | setg so=0 siso=0 | setl so=-1 siso=-1
let v:this_session=expand("<sfile>:p")
silent only
silent tabonly
cd ~/Lib/NAU/Mathematical_statistics/Labs/Lab_1
if expand('%') == '' && !&modified && line('$') <= 1 && getline(1) == ''
  let s:wipebuf = bufnr('%')
endif
let s:shortmess_save = &shortmess
if &shortmess =~ 'A'
  set shortmess=aoOA
else
  set shortmess=aoO
endif
badd +87 main.cpp
badd +3 types.hpp
badd +15 statistics/relativeFrequencyChart.hpp
badd +23 statistics/relativeFrequencyChart.cpp
badd +1 statistics/varSeries.cpp
badd +1 statistics/varSeries.hpp
badd +1 statistics/dataSeries.cpp
badd +12 statistics/dataSeries.hpp
badd +1 statistics/classSeries.cpp
badd +32 statistics/classSeries.hpp
badd +17 ~/Lib/NAU/Mathematical_statistics/Labs/Lab_1/statistics/distributionChart.hpp
badd +43 statistics/distributionChart.cpp
badd +221 ~/Lib/NAU/Mathematical_statistics/Labs/Lab_1/statistics/dataVector.cpp
badd +59 statistics/dataVector.hpp
badd +56 ~/Lib/NAU/Mathematical_statistics/Labs/Lab_1/statistics/chartViewBase.cpp
badd +33 ~/Lib/NAU/Mathematical_statistics/Labs/Lab_1/statistics/chartViewBase.hpp
badd +200 ../data/200/KVANT.DAT
badd +13 ../data/25/norm.txt
argglobal
%argdel
$argadd main.cpp
tabnew +setlocal\ bufhidden=wipe
tabnew +setlocal\ bufhidden=wipe
tabnew +setlocal\ bufhidden=wipe
tabnew +setlocal\ bufhidden=wipe
tabnew +setlocal\ bufhidden=wipe
tabnew +setlocal\ bufhidden=wipe
tabnew +setlocal\ bufhidden=wipe
tabrewind
edit main.cpp
argglobal
setlocal fdm=manual
setlocal fde=0
setlocal fmr={{{,}}}
setlocal fdi=#
setlocal fdl=0
setlocal fml=1
setlocal fdn=20
setlocal fen
silent! normal! zE
let &fdl = &fdl
let s:l = 33 - ((32 * winheight(0) + 21) / 42)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 33
normal! 05|
tabnext
edit ~/Lib/NAU/Mathematical_statistics/Labs/Lab_1/statistics/chartViewBase.cpp
let s:save_splitbelow = &splitbelow
let s:save_splitright = &splitright
set splitbelow splitright
wincmd _ | wincmd |
vsplit
wincmd _ | wincmd |
vsplit
2wincmd h
wincmd w
wincmd w
let &splitbelow = s:save_splitbelow
let &splitright = s:save_splitright
wincmd t
let s:save_winminheight = &winminheight
let s:save_winminwidth = &winminwidth
set winminheight=0
set winheight=1
set winminwidth=0
set winwidth=1
exe 'vert 1resize ' . ((&columns * 131 + 106) / 213)
exe 'vert 2resize ' . ((&columns * 79 + 106) / 213)
exe 'vert 3resize ' . ((&columns * 1 + 106) / 213)
argglobal
balt ~/Lib/NAU/Mathematical_statistics/Labs/Lab_1/statistics/chartViewBase.hpp
setlocal fdm=manual
setlocal fde=0
setlocal fmr={{{,}}}
setlocal fdi=#
setlocal fdl=0
setlocal fml=1
setlocal fdn=20
setlocal fen
silent! normal! zE
let &fdl = &fdl
let s:l = 56 - ((10 * winheight(0) + 21) / 42)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 56
normal! 031|
wincmd w
argglobal
if bufexists(fnamemodify("~/Lib/NAU/Mathematical_statistics/Labs/Lab_1/statistics/chartViewBase.hpp", ":p")) | buffer ~/Lib/NAU/Mathematical_statistics/Labs/Lab_1/statistics/chartViewBase.hpp | else | edit ~/Lib/NAU/Mathematical_statistics/Labs/Lab_1/statistics/chartViewBase.hpp | endif
if &buftype ==# 'terminal'
  silent file ~/Lib/NAU/Mathematical_statistics/Labs/Lab_1/statistics/chartViewBase.hpp
endif
balt ~/Lib/NAU/Mathematical_statistics/Labs/Lab_1/statistics/chartViewBase.cpp
setlocal fdm=manual
setlocal fde=0
setlocal fmr={{{,}}}
setlocal fdi=#
setlocal fdl=0
setlocal fml=1
setlocal fdn=20
setlocal fen
silent! normal! zE
let &fdl = &fdl
let s:l = 47 - ((32 * winheight(0) + 21) / 42)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 47
normal! 04|
wincmd w
argglobal
if bufexists(fnamemodify("~/Lib/NAU/Mathematical_statistics/Labs/Lab_1/statistics/chartViewBase.hpp", ":p")) | buffer ~/Lib/NAU/Mathematical_statistics/Labs/Lab_1/statistics/chartViewBase.hpp | else | edit ~/Lib/NAU/Mathematical_statistics/Labs/Lab_1/statistics/chartViewBase.hpp | endif
if &buftype ==# 'terminal'
  silent file ~/Lib/NAU/Mathematical_statistics/Labs/Lab_1/statistics/chartViewBase.hpp
endif
balt ~/Lib/NAU/Mathematical_statistics/Labs/Lab_1/statistics/chartViewBase.cpp
setlocal fdm=manual
setlocal fde=0
setlocal fmr={{{,}}}
setlocal fdi=#
setlocal fdl=0
setlocal fml=1
setlocal fdn=20
setlocal fen
silent! normal! zE
let &fdl = &fdl
let s:l = 35 - ((0 * winheight(0) + 21) / 42)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 35
normal! 08|
wincmd w
exe 'vert 1resize ' . ((&columns * 131 + 106) / 213)
exe 'vert 2resize ' . ((&columns * 79 + 106) / 213)
exe 'vert 3resize ' . ((&columns * 1 + 106) / 213)
tabnext
edit statistics/relativeFrequencyChart.cpp
let s:save_splitbelow = &splitbelow
let s:save_splitright = &splitright
set splitbelow splitright
wincmd _ | wincmd |
vsplit
wincmd _ | wincmd |
vsplit
2wincmd h
wincmd w
wincmd w
let &splitbelow = s:save_splitbelow
let &splitright = s:save_splitright
wincmd t
let s:save_winminheight = &winminheight
let s:save_winminwidth = &winminwidth
set winminheight=0
set winheight=1
set winminwidth=0
set winwidth=1
exe 'vert 1resize ' . ((&columns * 105 + 106) / 213)
exe 'vert 2resize ' . ((&columns * 106 + 106) / 213)
exe 'vert 3resize ' . ((&columns * 0 + 106) / 213)
argglobal
balt statistics/relativeFrequencyChart.hpp
setlocal fdm=manual
setlocal fde=0
setlocal fmr={{{,}}}
setlocal fdi=#
setlocal fdl=0
setlocal fml=1
setlocal fdn=20
setlocal fen
silent! normal! zE
let &fdl = &fdl
let s:l = 31 - ((30 * winheight(0) + 21) / 42)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 31
normal! 05|
wincmd w
argglobal
if bufexists(fnamemodify("statistics/relativeFrequencyChart.hpp", ":p")) | buffer statistics/relativeFrequencyChart.hpp | else | edit statistics/relativeFrequencyChart.hpp | endif
if &buftype ==# 'terminal'
  silent file statistics/relativeFrequencyChart.hpp
endif
balt statistics/relativeFrequencyChart.cpp
setlocal fdm=manual
setlocal fde=0
setlocal fmr={{{,}}}
setlocal fdi=#
setlocal fdl=0
setlocal fml=1
setlocal fdn=20
setlocal fen
silent! normal! zE
let &fdl = &fdl
let s:l = 15 - ((14 * winheight(0) + 21) / 42)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 15
normal! 0
wincmd w
argglobal
if bufexists(fnamemodify("statistics/relativeFrequencyChart.hpp", ":p")) | buffer statistics/relativeFrequencyChart.hpp | else | edit statistics/relativeFrequencyChart.hpp | endif
if &buftype ==# 'terminal'
  silent file statistics/relativeFrequencyChart.hpp
endif
balt statistics/relativeFrequencyChart.cpp
setlocal fdm=manual
setlocal fde=0
setlocal fmr={{{,}}}
setlocal fdi=#
setlocal fdl=0
setlocal fml=1
setlocal fdn=20
setlocal fen
silent! normal! zE
let &fdl = &fdl
let s:l = 15 - ((14 * winheight(0) + 21) / 42)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 15
normal! 017|
wincmd w
exe 'vert 1resize ' . ((&columns * 105 + 106) / 213)
exe 'vert 2resize ' . ((&columns * 106 + 106) / 213)
exe 'vert 3resize ' . ((&columns * 0 + 106) / 213)
tabnext
edit statistics/distributionChart.cpp
let s:save_splitbelow = &splitbelow
let s:save_splitright = &splitright
set splitbelow splitright
wincmd _ | wincmd |
vsplit
1wincmd h
wincmd w
let &splitbelow = s:save_splitbelow
let &splitright = s:save_splitright
wincmd t
let s:save_winminheight = &winminheight
let s:save_winminwidth = &winminwidth
set winminheight=0
set winheight=1
set winminwidth=0
set winwidth=1
exe 'vert 1resize ' . ((&columns * 105 + 106) / 213)
exe 'vert 2resize ' . ((&columns * 107 + 106) / 213)
argglobal
balt ~/Lib/NAU/Mathematical_statistics/Labs/Lab_1/statistics/distributionChart.hpp
setlocal fdm=manual
setlocal fde=0
setlocal fmr={{{,}}}
setlocal fdi=#
setlocal fdl=0
setlocal fml=1
setlocal fdn=20
setlocal fen
silent! normal! zE
let &fdl = &fdl
let s:l = 43 - ((27 * winheight(0) + 21) / 42)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 43
normal! 028|
wincmd w
argglobal
if bufexists(fnamemodify("~/Lib/NAU/Mathematical_statistics/Labs/Lab_1/statistics/distributionChart.hpp", ":p")) | buffer ~/Lib/NAU/Mathematical_statistics/Labs/Lab_1/statistics/distributionChart.hpp | else | edit ~/Lib/NAU/Mathematical_statistics/Labs/Lab_1/statistics/distributionChart.hpp | endif
if &buftype ==# 'terminal'
  silent file ~/Lib/NAU/Mathematical_statistics/Labs/Lab_1/statistics/distributionChart.hpp
endif
balt statistics/distributionChart.cpp
setlocal fdm=manual
setlocal fde=0
setlocal fmr={{{,}}}
setlocal fdi=#
setlocal fdl=0
setlocal fml=1
setlocal fdn=20
setlocal fen
silent! normal! zE
let &fdl = &fdl
let s:l = 14 - ((13 * winheight(0) + 21) / 42)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 14
normal! 0
wincmd w
exe 'vert 1resize ' . ((&columns * 105 + 106) / 213)
exe 'vert 2resize ' . ((&columns * 107 + 106) / 213)
tabnext
edit ~/Lib/NAU/Mathematical_statistics/Labs/Lab_1/statistics/dataVector.cpp
let s:save_splitbelow = &splitbelow
let s:save_splitright = &splitright
set splitbelow splitright
wincmd _ | wincmd |
vsplit
1wincmd h
wincmd w
let &splitbelow = s:save_splitbelow
let &splitright = s:save_splitright
wincmd t
let s:save_winminheight = &winminheight
let s:save_winminwidth = &winminwidth
set winminheight=0
set winheight=1
set winminwidth=0
set winwidth=1
exe '1resize ' . ((&lines * 37 + 22) / 45)
exe 'vert 1resize ' . ((&columns * 67 + 106) / 213)
exe '2resize ' . ((&lines * 37 + 22) / 45)
exe 'vert 2resize ' . ((&columns * 145 + 106) / 213)
argglobal
balt statistics/dataVector.hpp
setlocal fdm=manual
setlocal fde=0
setlocal fmr={{{,}}}
setlocal fdi=#
setlocal fdl=0
setlocal fml=1
setlocal fdn=20
setlocal fen
silent! normal! zE
let &fdl = &fdl
let s:l = 221 - ((11 * winheight(0) + 18) / 37)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 221
normal! 043|
wincmd w
argglobal
if bufexists(fnamemodify("statistics/dataVector.hpp", ":p")) | buffer statistics/dataVector.hpp | else | edit statistics/dataVector.hpp | endif
if &buftype ==# 'terminal'
  silent file statistics/dataVector.hpp
endif
balt ~/Lib/NAU/Mathematical_statistics/Labs/Lab_1/statistics/dataVector.cpp
setlocal fdm=manual
setlocal fde=0
setlocal fmr={{{,}}}
setlocal fdi=#
setlocal fdl=0
setlocal fml=1
setlocal fdn=20
setlocal fen
silent! normal! zE
let &fdl = &fdl
let s:l = 47 - ((28 * winheight(0) + 18) / 37)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 47
normal! 0
wincmd w
exe '1resize ' . ((&lines * 37 + 22) / 45)
exe 'vert 1resize ' . ((&columns * 67 + 106) / 213)
exe '2resize ' . ((&lines * 37 + 22) / 45)
exe 'vert 2resize ' . ((&columns * 145 + 106) / 213)
tabnext
edit statistics/dataSeries.cpp
let s:save_splitbelow = &splitbelow
let s:save_splitright = &splitright
set splitbelow splitright
wincmd _ | wincmd |
vsplit
1wincmd h
wincmd w
let &splitbelow = s:save_splitbelow
let &splitright = s:save_splitright
wincmd t
let s:save_winminheight = &winminheight
let s:save_winminwidth = &winminwidth
set winminheight=0
set winheight=1
set winminwidth=0
set winwidth=1
exe '1resize ' . ((&lines * 37 + 22) / 45)
exe 'vert 1resize ' . ((&columns * 75 + 106) / 213)
exe '2resize ' . ((&lines * 37 + 22) / 45)
exe 'vert 2resize ' . ((&columns * 137 + 106) / 213)
argglobal
balt statistics/dataSeries.hpp
setlocal fdm=manual
setlocal fde=0
setlocal fmr={{{,}}}
setlocal fdi=#
setlocal fdl=0
setlocal fml=1
setlocal fdn=20
setlocal fen
silent! normal! zE
let &fdl = &fdl
let s:l = 83 - ((20 * winheight(0) + 18) / 37)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 83
normal! 0
wincmd w
argglobal
if bufexists(fnamemodify("statistics/dataSeries.hpp", ":p")) | buffer statistics/dataSeries.hpp | else | edit statistics/dataSeries.hpp | endif
if &buftype ==# 'terminal'
  silent file statistics/dataSeries.hpp
endif
balt statistics/dataSeries.cpp
setlocal fdm=manual
setlocal fde=0
setlocal fmr={{{,}}}
setlocal fdi=#
setlocal fdl=0
setlocal fml=1
setlocal fdn=20
setlocal fen
silent! normal! zE
let &fdl = &fdl
let s:l = 12 - ((0 * winheight(0) + 18) / 37)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 12
normal! 015|
wincmd w
exe '1resize ' . ((&lines * 37 + 22) / 45)
exe 'vert 1resize ' . ((&columns * 75 + 106) / 213)
exe '2resize ' . ((&lines * 37 + 22) / 45)
exe 'vert 2resize ' . ((&columns * 137 + 106) / 213)
tabnext
edit statistics/varSeries.cpp
let s:save_splitbelow = &splitbelow
let s:save_splitright = &splitright
set splitbelow splitright
wincmd _ | wincmd |
vsplit
1wincmd h
wincmd w
let &splitbelow = s:save_splitbelow
let &splitright = s:save_splitright
wincmd t
let s:save_winminheight = &winminheight
let s:save_winminwidth = &winminwidth
set winminheight=0
set winheight=1
set winminwidth=0
set winwidth=1
exe '1resize ' . ((&lines * 37 + 22) / 45)
exe 'vert 1resize ' . ((&columns * 61 + 106) / 213)
exe '2resize ' . ((&lines * 37 + 22) / 45)
exe 'vert 2resize ' . ((&columns * 151 + 106) / 213)
argglobal
balt statistics/varSeries.hpp
setlocal fdm=manual
setlocal fde=0
setlocal fmr={{{,}}}
setlocal fdi=#
setlocal fdl=0
setlocal fml=1
setlocal fdn=20
setlocal fen
silent! normal! zE
let &fdl = &fdl
let s:l = 36 - ((35 * winheight(0) + 18) / 37)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 36
normal! 0
wincmd w
argglobal
if bufexists(fnamemodify("statistics/varSeries.hpp", ":p")) | buffer statistics/varSeries.hpp | else | edit statistics/varSeries.hpp | endif
if &buftype ==# 'terminal'
  silent file statistics/varSeries.hpp
endif
balt statistics/varSeries.cpp
setlocal fdm=manual
setlocal fde=0
setlocal fmr={{{,}}}
setlocal fdi=#
setlocal fdl=0
setlocal fml=1
setlocal fdn=20
setlocal fen
silent! normal! zE
let &fdl = &fdl
let s:l = 16 - ((0 * winheight(0) + 18) / 37)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 16
normal! 022|
wincmd w
exe '1resize ' . ((&lines * 37 + 22) / 45)
exe 'vert 1resize ' . ((&columns * 61 + 106) / 213)
exe '2resize ' . ((&lines * 37 + 22) / 45)
exe 'vert 2resize ' . ((&columns * 151 + 106) / 213)
tabnext
edit statistics/classSeries.cpp
let s:save_splitbelow = &splitbelow
let s:save_splitright = &splitright
set splitbelow splitright
wincmd _ | wincmd |
vsplit
1wincmd h
wincmd w
let &splitbelow = s:save_splitbelow
let &splitright = s:save_splitright
wincmd t
let s:save_winminheight = &winminheight
let s:save_winminwidth = &winminwidth
set winminheight=0
set winheight=1
set winminwidth=0
set winwidth=1
exe 'vert 1resize ' . ((&columns * 91 + 106) / 213)
exe 'vert 2resize ' . ((&columns * 121 + 106) / 213)
argglobal
balt statistics/classSeries.hpp
setlocal fdm=manual
setlocal fde=0
setlocal fmr={{{,}}}
setlocal fdi=#
setlocal fdl=0
setlocal fml=1
setlocal fdn=20
setlocal fen
silent! normal! zE
let &fdl = &fdl
let s:l = 33 - ((26 * winheight(0) + 22) / 45)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 33
normal! 018|
wincmd w
argglobal
if bufexists(fnamemodify("statistics/classSeries.hpp", ":p")) | buffer statistics/classSeries.hpp | else | edit statistics/classSeries.hpp | endif
if &buftype ==# 'terminal'
  silent file statistics/classSeries.hpp
endif
balt statistics/classSeries.cpp
setlocal fdm=manual
setlocal fde=0
setlocal fmr={{{,}}}
setlocal fdi=#
setlocal fdl=0
setlocal fml=1
setlocal fdn=20
setlocal fen
silent! normal! zE
let &fdl = &fdl
let s:l = 10 - ((9 * winheight(0) + 22) / 45)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 10
normal! 0
wincmd w
exe 'vert 1resize ' . ((&columns * 91 + 106) / 213)
exe 'vert 2resize ' . ((&columns * 121 + 106) / 213)
tabnext 2
if exists('s:wipebuf') && len(win_findbuf(s:wipebuf)) == 0 && getbufvar(s:wipebuf, '&buftype') isnot# 'terminal'
  silent exe 'bwipe ' . s:wipebuf
endif
unlet! s:wipebuf
set winheight=1 winwidth=20
let &shortmess = s:shortmess_save
let &winminheight = s:save_winminheight
let &winminwidth = s:save_winminwidth
let s:sx = expand("<sfile>:p:r")."x.vim"
if filereadable(s:sx)
  exe "source " . fnameescape(s:sx)
endif
let &g:so = s:so_save | let &g:siso = s:siso_save
set hlsearch
let g:this_session = v:this_session
let g:this_obsession = v:this_session
doautoall SessionLoadPost
unlet SessionLoad
" vim: set ft=vim :
