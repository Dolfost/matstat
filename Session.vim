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
badd +10 main.cpp
badd +1 include/statistics/plotBase.cpp
badd +61 include/statistics/plotBase.hpp
badd +85 include/statistics/dataSeries.cpp
badd +15 include/statistics/dataSeries.hpp
badd +33 include/statistics/dataVector.hpp
badd +14 include/statistics/dataVector.cpp
badd +1 include/statistics/classSeries.cpp
badd +14 include/statistics/classSeries.hpp
badd +27 include/statistics/distributionChart.cpp
badd +15 include/statistics/distributionChart.hpp
badd +4 include/types.hpp
badd +14 include/statistics/densityChart.hpp
badd +1 include/statistics/densityChart.cpp
badd +47 include/gui/mainWindow.hpp
badd +135 include/gui/mainWindow.cpp
badd +34 include/gui/vectorContainer.cpp
badd +24 include/gui/vectorContainer.hpp
badd +18 CMakeLists.txt
badd +80 include/gui/vectorPicker.cpp
badd +23 include/gui/vectorPicker.hpp
argglobal
%argdel
tabnew +setlocal\ bufhidden=wipe
tabnew +setlocal\ bufhidden=wipe
tabnew +setlocal\ bufhidden=wipe
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
let s:l = 9 - ((8 * winheight(0) + 17) / 35)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 9
normal! 0
tabnext
edit include/statistics/plotBase.cpp
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
exe '1resize ' . ((&lines * 34 + 21) / 42)
exe 'vert 1resize ' . ((&columns * 116 + 106) / 213)
exe '2resize ' . ((&lines * 34 + 21) / 42)
exe 'vert 2resize ' . ((&columns * 96 + 106) / 213)
argglobal
balt include/statistics/plotBase.hpp
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
let s:l = 222 - ((25 * winheight(0) + 17) / 34)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 222
normal! 013|
wincmd w
argglobal
if bufexists(fnamemodify("include/statistics/plotBase.hpp", ":p")) | buffer include/statistics/plotBase.hpp | else | edit include/statistics/plotBase.hpp | endif
if &buftype ==# 'terminal'
  silent file include/statistics/plotBase.hpp
endif
balt include/statistics/plotBase.cpp
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
let s:l = 59 - ((0 * winheight(0) + 17) / 34)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 59
normal! 05|
wincmd w
exe '1resize ' . ((&lines * 34 + 21) / 42)
exe 'vert 1resize ' . ((&columns * 116 + 106) / 213)
exe '2resize ' . ((&lines * 34 + 21) / 42)
exe 'vert 2resize ' . ((&columns * 96 + 106) / 213)
tabnext
edit include/statistics/densityChart.cpp
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
exe '1resize ' . ((&lines * 34 + 21) / 42)
exe 'vert 1resize ' . ((&columns * 99 + 106) / 213)
exe '2resize ' . ((&lines * 34 + 21) / 42)
exe 'vert 2resize ' . ((&columns * 113 + 106) / 213)
argglobal
balt include/statistics/densityChart.hpp
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
let s:l = 8 - ((7 * winheight(0) + 17) / 34)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 8
normal! 027|
wincmd w
argglobal
if bufexists(fnamemodify("include/statistics/densityChart.hpp", ":p")) | buffer include/statistics/densityChart.hpp | else | edit include/statistics/densityChart.hpp | endif
if &buftype ==# 'terminal'
  silent file include/statistics/densityChart.hpp
endif
balt include/statistics/densityChart.cpp
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
let s:l = 19 - ((0 * winheight(0) + 17) / 34)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 19
normal! 028|
wincmd w
exe '1resize ' . ((&lines * 34 + 21) / 42)
exe 'vert 1resize ' . ((&columns * 99 + 106) / 213)
exe '2resize ' . ((&lines * 34 + 21) / 42)
exe 'vert 2resize ' . ((&columns * 113 + 106) / 213)
tabnext
edit include/statistics/distributionChart.cpp
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
exe 'vert 1resize ' . ((&columns * 99 + 106) / 213)
exe 'vert 2resize ' . ((&columns * 113 + 106) / 213)
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
let s:l = 27 - ((26 * winheight(0) + 19) / 39)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 27
normal! 0
wincmd w
argglobal
if bufexists(fnamemodify("include/statistics/distributionChart.hpp", ":p")) | buffer include/statistics/distributionChart.hpp | else | edit include/statistics/distributionChart.hpp | endif
if &buftype ==# 'terminal'
  silent file include/statistics/distributionChart.hpp
endif
balt include/statistics/distributionChart.cpp
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
let s:l = 15 - ((14 * winheight(0) + 19) / 39)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 15
normal! 021|
wincmd w
exe 'vert 1resize ' . ((&columns * 99 + 106) / 213)
exe 'vert 2resize ' . ((&columns * 113 + 106) / 213)
tabnext
edit include/gui/vectorContainer.cpp
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
exe 'vert 1resize ' . ((&columns * 106 + 106) / 213)
exe 'vert 2resize ' . ((&columns * 106 + 106) / 213)
argglobal
balt include/gui/vectorContainer.hpp
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
let s:l = 34 - ((19 * winheight(0) + 19) / 39)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 34
normal! 028|
wincmd w
argglobal
if bufexists(fnamemodify("include/gui/vectorContainer.hpp", ":p")) | buffer include/gui/vectorContainer.hpp | else | edit include/gui/vectorContainer.hpp | endif
if &buftype ==# 'terminal'
  silent file include/gui/vectorContainer.hpp
endif
balt include/gui/vectorContainer.cpp
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
let s:l = 24 - ((23 * winheight(0) + 19) / 39)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 24
normal! 046|
wincmd w
exe 'vert 1resize ' . ((&columns * 106 + 106) / 213)
exe 'vert 2resize ' . ((&columns * 106 + 106) / 213)
tabnext
edit include/gui/mainWindow.cpp
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
exe 'vert 1resize ' . ((&columns * 106 + 106) / 213)
exe 'vert 2resize ' . ((&columns * 106 + 106) / 213)
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
let s:l = 135 - ((18 * winheight(0) + 19) / 39)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 135
normal! 0
wincmd w
argglobal
if bufexists(fnamemodify("include/gui/mainWindow.hpp", ":p")) | buffer include/gui/mainWindow.hpp | else | edit include/gui/mainWindow.hpp | endif
if &buftype ==# 'terminal'
  silent file include/gui/mainWindow.hpp
endif
balt include/statistics/densityChart.cpp
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
let s:l = 47 - ((34 * winheight(0) + 19) / 39)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 47
normal! 02|
wincmd w
exe 'vert 1resize ' . ((&columns * 106 + 106) / 213)
exe 'vert 2resize ' . ((&columns * 106 + 106) / 213)
tabnext
edit include/gui/vectorPicker.cpp
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
exe '1resize ' . ((&lines * 33 + 21) / 42)
exe 'vert 1resize ' . ((&columns * 122 + 106) / 213)
exe '2resize ' . ((&lines * 33 + 21) / 42)
exe 'vert 2resize ' . ((&columns * 90 + 106) / 213)
argglobal
balt include/gui/vectorPicker.hpp
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
let s:l = 80 - ((8 * winheight(0) + 16) / 33)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 80
normal! 0
wincmd w
argglobal
if bufexists(fnamemodify("include/gui/vectorPicker.hpp", ":p")) | buffer include/gui/vectorPicker.hpp | else | edit include/gui/vectorPicker.hpp | endif
if &buftype ==# 'terminal'
  silent file include/gui/vectorPicker.hpp
endif
balt include/gui/vectorPicker.cpp
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
let s:l = 30 - ((18 * winheight(0) + 16) / 33)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 30
normal! 013|
wincmd w
exe '1resize ' . ((&lines * 33 + 21) / 42)
exe 'vert 1resize ' . ((&columns * 122 + 106) / 213)
exe '2resize ' . ((&lines * 33 + 21) / 42)
exe 'vert 2resize ' . ((&columns * 90 + 106) / 213)
tabnext
edit include/statistics/dataSeries.cpp
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
exe '1resize ' . ((&lines * 35 + 21) / 42)
exe 'vert 1resize ' . ((&columns * 105 + 106) / 213)
exe '2resize ' . ((&lines * 35 + 21) / 42)
exe 'vert 2resize ' . ((&columns * 107 + 106) / 213)
argglobal
balt include/statistics/dataSeries.hpp
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
let s:l = 85 - ((22 * winheight(0) + 17) / 35)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 85
normal! 0
wincmd w
argglobal
if bufexists(fnamemodify("include/statistics/dataSeries.hpp", ":p")) | buffer include/statistics/dataSeries.hpp | else | edit include/statistics/dataSeries.hpp | endif
if &buftype ==# 'terminal'
  silent file include/statistics/dataSeries.hpp
endif
balt include/statistics/dataSeries.cpp
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
let s:l = 15 - ((8 * winheight(0) + 17) / 35)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 15
normal! 05|
wincmd w
exe '1resize ' . ((&lines * 35 + 21) / 42)
exe 'vert 1resize ' . ((&columns * 105 + 106) / 213)
exe '2resize ' . ((&lines * 35 + 21) / 42)
exe 'vert 2resize ' . ((&columns * 107 + 106) / 213)
tabnext
edit include/statistics/dataVector.cpp
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
exe '1resize ' . ((&lines * 35 + 21) / 42)
exe 'vert 1resize ' . ((&columns * 79 + 106) / 213)
exe '2resize ' . ((&lines * 35 + 21) / 42)
exe 'vert 2resize ' . ((&columns * 133 + 106) / 213)
argglobal
balt include/statistics/dataVector.hpp
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
let s:l = 21 - ((20 * winheight(0) + 17) / 35)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 21
normal! 0
wincmd w
argglobal
if bufexists(fnamemodify("include/statistics/dataVector.hpp", ":p")) | buffer include/statistics/dataVector.hpp | else | edit include/statistics/dataVector.hpp | endif
if &buftype ==# 'terminal'
  silent file include/statistics/dataVector.hpp
endif
balt include/statistics/dataVector.cpp
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
let s:l = 33 - ((12 * winheight(0) + 17) / 35)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 33
normal! 010|
wincmd w
exe '1resize ' . ((&lines * 35 + 21) / 42)
exe 'vert 1resize ' . ((&columns * 79 + 106) / 213)
exe '2resize ' . ((&lines * 35 + 21) / 42)
exe 'vert 2resize ' . ((&columns * 133 + 106) / 213)
tabnext
edit include/statistics/classSeries.cpp
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
exe '1resize ' . ((&lines * 35 + 21) / 42)
exe 'vert 1resize ' . ((&columns * 99 + 106) / 213)
exe '2resize ' . ((&lines * 35 + 21) / 42)
exe 'vert 2resize ' . ((&columns * 113 + 106) / 213)
argglobal
balt include/statistics/classSeries.hpp
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
let s:l = 57 - ((21 * winheight(0) + 17) / 35)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 57
normal! 0
wincmd w
argglobal
if bufexists(fnamemodify("include/statistics/classSeries.hpp", ":p")) | buffer include/statistics/classSeries.hpp | else | edit include/statistics/classSeries.hpp | endif
if &buftype ==# 'terminal'
  silent file include/statistics/classSeries.hpp
endif
balt include/statistics/classSeries.cpp
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
let s:l = 14 - ((13 * winheight(0) + 17) / 35)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 14
normal! 0
wincmd w
exe '1resize ' . ((&lines * 35 + 21) / 42)
exe 'vert 1resize ' . ((&columns * 99 + 106) / 213)
exe '2resize ' . ((&lines * 35 + 21) / 42)
exe 'vert 2resize ' . ((&columns * 113 + 106) / 213)
tabnext
edit include/types.hpp
argglobal
balt include/statistics/classSeries.cpp
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
let s:l = 1 - ((0 * winheight(0) + 17) / 35)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 1
normal! 0
tabnext 6
if exists('s:wipebuf') && len(win_findbuf(s:wipebuf)) == 0 && getbufvar(s:wipebuf, '&buftype') isnot# 'terminal'
  silent exe 'bwipe ' . s:wipebuf
endif
unlet! s:wipebuf
set winheight=1 winwidth=20
let &shortmess = s:shortmess_save
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
