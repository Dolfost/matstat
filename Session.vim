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
badd +17 main.cpp
badd +17 calculator.hpp
badd +1 calculator.cpp
badd +3 types.hpp
badd +18 statistics/varseries.hpp
badd +1 statistics/varseries.cpp
badd +1 ~/Lib/NAU/Mathematical_statistics/Labs/Lab_1/statistics/classseries.cpp
badd +11 ~/Lib/NAU/Mathematical_statistics/Labs/Lab_1/statistics/classseries.hpp
badd +1 ~/Lib/NAU/Mathematical_statistics/Labs/Lab_1/statistics/dataseries.cpp
badd +30 ~/Lib/NAU/Mathematical_statistics/Labs/Lab_1/statistics/dataseries.hpp
badd +3 ~/Lib/NAU/Mathematical_statistics/Labs/Lab_1/statistics/graph.hpp
badd +13 ~/Lib/NAU/Mathematical_statistics/Labs/Lab_1/statistics/chart.hpp
badd +1 ~/Lib/NAU/Mathematical_statistics/Labs/Lab_1/statistics/chart.cpp
badd +1 gui/vectorContainerWidget.cpp
badd +5 gui/vectorContainerWidget.hpp
badd +1 gui/vectorReaderWindow.cpp
badd +23 gui/vectorReaderWindow.hpp
badd +1 statistics/vectordataseries.cpp
badd +6 statistics/vectordataseries.hpp
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
let s:l = 17 - ((16 * winheight(0) + 25) / 50)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 17
normal! 04|
tabnext
edit ~/Lib/NAU/Mathematical_statistics/Labs/Lab_1/statistics/chart.cpp
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
exe 'vert 1resize ' . ((&columns * 92 + 96) / 192)
exe 'vert 2resize ' . ((&columns * 99 + 96) / 192)
argglobal
balt ~/Lib/NAU/Mathematical_statistics/Labs/Lab_1/statistics/graph.hpp
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
let s:l = 7 - ((6 * winheight(0) + 25) / 50)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 7
normal! 05|
wincmd w
argglobal
if bufexists(fnamemodify("~/Lib/NAU/Mathematical_statistics/Labs/Lab_1/statistics/chart.hpp", ":p")) | buffer ~/Lib/NAU/Mathematical_statistics/Labs/Lab_1/statistics/chart.hpp | else | edit ~/Lib/NAU/Mathematical_statistics/Labs/Lab_1/statistics/chart.hpp | endif
if &buftype ==# 'terminal'
  silent file ~/Lib/NAU/Mathematical_statistics/Labs/Lab_1/statistics/chart.hpp
endif
balt ~/Lib/NAU/Mathematical_statistics/Labs/Lab_1/statistics/chart.cpp
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
let s:l = 16 - ((15 * winheight(0) + 25) / 50)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 16
normal! 0
wincmd w
exe 'vert 1resize ' . ((&columns * 92 + 96) / 192)
exe 'vert 2resize ' . ((&columns * 99 + 96) / 192)
tabnext
edit calculator.cpp
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
exe 'vert 1resize ' . ((&columns * 93 + 96) / 192)
exe 'vert 2resize ' . ((&columns * 98 + 96) / 192)
argglobal
balt calculator.hpp
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
let s:l = 10 - ((8 * winheight(0) + 25) / 50)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 10
normal! 012|
wincmd w
argglobal
if bufexists(fnamemodify("calculator.hpp", ":p")) | buffer calculator.hpp | else | edit calculator.hpp | endif
if &buftype ==# 'terminal'
  silent file calculator.hpp
endif
balt calculator.cpp
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
let s:l = 20 - ((19 * winheight(0) + 25) / 50)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 20
normal! 010|
wincmd w
exe 'vert 1resize ' . ((&columns * 93 + 96) / 192)
exe 'vert 2resize ' . ((&columns * 98 + 96) / 192)
tabnext
edit gui/vectorContainerWidget.cpp
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
exe 'vert 1resize ' . ((&columns * 86 + 96) / 192)
exe 'vert 2resize ' . ((&columns * 105 + 96) / 192)
argglobal
balt gui/vectorContainerWidget.hpp
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
let s:l = 1 - ((0 * winheight(0) + 25) / 50)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 1
normal! 036|
wincmd w
argglobal
if bufexists(fnamemodify("gui/vectorContainerWidget.hpp", ":p")) | buffer gui/vectorContainerWidget.hpp | else | edit gui/vectorContainerWidget.hpp | endif
if &buftype ==# 'terminal'
  silent file gui/vectorContainerWidget.hpp
endif
balt gui/vectorContainerWidget.cpp
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
let s:l = 18 - ((17 * winheight(0) + 25) / 50)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 18
normal! 07|
wincmd w
exe 'vert 1resize ' . ((&columns * 86 + 96) / 192)
exe 'vert 2resize ' . ((&columns * 105 + 96) / 192)
tabnext
edit gui/vectorReaderWindow.cpp
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
exe 'vert 1resize ' . ((&columns * 77 + 96) / 192)
exe 'vert 2resize ' . ((&columns * 114 + 96) / 192)
argglobal
balt gui/vectorReaderWindow.hpp
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
let s:l = 47 - ((34 * winheight(0) + 25) / 50)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 47
normal! 017|
wincmd w
argglobal
if bufexists(fnamemodify("gui/vectorReaderWindow.hpp", ":p")) | buffer gui/vectorReaderWindow.hpp | else | edit gui/vectorReaderWindow.hpp | endif
if &buftype ==# 'terminal'
  silent file gui/vectorReaderWindow.hpp
endif
balt gui/vectorReaderWindow.cpp
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
let s:l = 23 - ((22 * winheight(0) + 25) / 50)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 23
normal! 046|
wincmd w
exe 'vert 1resize ' . ((&columns * 77 + 96) / 192)
exe 'vert 2resize ' . ((&columns * 114 + 96) / 192)
tabnext
edit ~/Lib/NAU/Mathematical_statistics/Labs/Lab_1/statistics/dataseries.cpp
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
exe 'vert 1resize ' . ((&columns * 95 + 96) / 192)
exe 'vert 2resize ' . ((&columns * 96 + 96) / 192)
argglobal
balt ~/Lib/NAU/Mathematical_statistics/Labs/Lab_1/statistics/dataseries.hpp
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
let s:l = 61 - ((13 * winheight(0) + 25) / 50)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 61
normal! 030|
wincmd w
argglobal
if bufexists(fnamemodify("~/Lib/NAU/Mathematical_statistics/Labs/Lab_1/statistics/dataseries.hpp", ":p")) | buffer ~/Lib/NAU/Mathematical_statistics/Labs/Lab_1/statistics/dataseries.hpp | else | edit ~/Lib/NAU/Mathematical_statistics/Labs/Lab_1/statistics/dataseries.hpp | endif
if &buftype ==# 'terminal'
  silent file ~/Lib/NAU/Mathematical_statistics/Labs/Lab_1/statistics/dataseries.hpp
endif
balt ~/Lib/NAU/Mathematical_statistics/Labs/Lab_1/statistics/dataseries.cpp
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
let s:l = 32 - ((31 * winheight(0) + 25) / 50)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 32
normal! 0
wincmd w
exe 'vert 1resize ' . ((&columns * 95 + 96) / 192)
exe 'vert 2resize ' . ((&columns * 96 + 96) / 192)
tabnext
edit statistics/vectordataseries.cpp
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
exe '1resize ' . ((&lines * 36 + 26) / 53)
exe 'vert 1resize ' . ((&columns * 95 + 96) / 192)
exe '2resize ' . ((&lines * 36 + 26) / 53)
exe 'vert 2resize ' . ((&columns * 96 + 96) / 192)
argglobal
balt statistics/vectordataseries.hpp
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
let s:l = 3 - ((2 * winheight(0) + 18) / 36)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 3
normal! 09|
wincmd w
argglobal
if bufexists(fnamemodify("statistics/vectordataseries.hpp", ":p")) | buffer statistics/vectordataseries.hpp | else | edit statistics/vectordataseries.hpp | endif
if &buftype ==# 'terminal'
  silent file statistics/vectordataseries.hpp
endif
balt statistics/vectordataseries.cpp
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
let s:l = 12 - ((11 * winheight(0) + 18) / 36)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 12
normal! 0
wincmd w
exe '1resize ' . ((&lines * 36 + 26) / 53)
exe 'vert 1resize ' . ((&columns * 95 + 96) / 192)
exe '2resize ' . ((&lines * 36 + 26) / 53)
exe 'vert 2resize ' . ((&columns * 96 + 96) / 192)
tabnext
edit statistics/varseries.cpp
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
exe '1resize ' . ((&lines * 36 + 26) / 53)
exe 'vert 1resize ' . ((&columns * 114 + 96) / 192)
exe '2resize ' . ((&lines * 36 + 26) / 53)
exe 'vert 2resize ' . ((&columns * 77 + 96) / 192)
argglobal
balt statistics/varseries.hpp
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
let s:l = 1 - ((0 * winheight(0) + 18) / 36)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 1
normal! 021|
wincmd w
argglobal
if bufexists(fnamemodify("statistics/varseries.hpp", ":p")) | buffer statistics/varseries.hpp | else | edit statistics/varseries.hpp | endif
if &buftype ==# 'terminal'
  silent file statistics/varseries.hpp
endif
balt statistics/varseries.cpp
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
let s:l = 18 - ((17 * winheight(0) + 18) / 36)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 18
normal! 05|
wincmd w
exe '1resize ' . ((&lines * 36 + 26) / 53)
exe 'vert 1resize ' . ((&columns * 114 + 96) / 192)
exe '2resize ' . ((&lines * 36 + 26) / 53)
exe 'vert 2resize ' . ((&columns * 77 + 96) / 192)
tabnext
edit ~/Lib/NAU/Mathematical_statistics/Labs/Lab_1/statistics/classseries.cpp
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
exe '1resize ' . ((&lines * 40 + 26) / 53)
exe 'vert 1resize ' . ((&columns * 107 + 96) / 192)
exe '2resize ' . ((&lines * 40 + 26) / 53)
exe 'vert 2resize ' . ((&columns * 84 + 96) / 192)
argglobal
balt statistics/varseries.cpp
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
let s:l = 45 - ((23 * winheight(0) + 20) / 40)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 45
normal! 012|
wincmd w
argglobal
if bufexists(fnamemodify("~/Lib/NAU/Mathematical_statistics/Labs/Lab_1/statistics/classseries.hpp", ":p")) | buffer ~/Lib/NAU/Mathematical_statistics/Labs/Lab_1/statistics/classseries.hpp | else | edit ~/Lib/NAU/Mathematical_statistics/Labs/Lab_1/statistics/classseries.hpp | endif
if &buftype ==# 'terminal'
  silent file ~/Lib/NAU/Mathematical_statistics/Labs/Lab_1/statistics/classseries.hpp
endif
balt ~/Lib/NAU/Mathematical_statistics/Labs/Lab_1/statistics/classseries.cpp
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
let s:l = 11 - ((0 * winheight(0) + 20) / 40)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 11
normal! 028|
wincmd w
exe '1resize ' . ((&lines * 40 + 26) / 53)
exe 'vert 1resize ' . ((&columns * 107 + 96) / 192)
exe '2resize ' . ((&lines * 40 + 26) / 53)
exe 'vert 2resize ' . ((&columns * 84 + 96) / 192)
tabnext 1
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
