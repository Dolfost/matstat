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
badd +14 main.cpp
badd +104 include/statistics/plotBase.cpp
badd +37 include/statistics/plotBase.hpp
badd +1 include/statistics/dataSeries.cpp
badd +16 include/statistics/dataSeries.hpp
badd +418 include/statistics/dataVector.hpp
badd +1 include/statistics/dataVector.cpp
badd +1 include/statistics/classSeries.cpp
badd +21 include/statistics/classSeries.hpp
badd +1 include/statistics/distributionChart.cpp
badd +18 include/statistics/distributionChart.hpp
badd +21 include/types.hpp
badd +19 include/statistics/densityChart.hpp
badd +1 include/statistics/densityChart.cpp
badd +49 include/gui/mainWindow.hpp
badd +1 include/gui/mainWindow.cpp
badd +24 CMakeLists.txt
badd +12 exprtk_cmake/readme.txt
badd +7 include/gui/Section.cpp
badd +24 include/gui/vectorContainerWidget.hpp
badd +1 include/gui/transformationFormulaEditorDialog.cpp
badd +3 include/gui/vectorPickerDialog.hpp
badd +36 include/gui/transformationFormulaEditorDialog.hpp
badd +1 include/gui/vectorPickerDialog.cpp
badd +27 include/gui/vectorContainerWidget.cpp
badd +40 include/gui/vectorInfoDialog.hpp
badd +1 include/gui/vectorInfoDialog.cpp
badd +18 include/statistics/varSeries.hpp
badd +87 include/gui/vectorProcessorWidget.hpp
badd +1 include/gui/vectorProcessorWidget.cpp
badd +6 include/gui/guiTypes.hpp
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
let s:l = 14 - ((12 * winheight(0) + 18) / 37)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 14
normal! 0
tabnext
edit include/gui/vectorInfoDialog.cpp
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
exe 'vert 1resize ' . ((&columns * 132 + 95) / 190)
exe 'vert 2resize ' . ((&columns * 57 + 95) / 190)
argglobal
balt include/gui/vectorInfoDialog.hpp
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
let s:l = 213 - ((16 * winheight(0) + 18) / 37)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 213
normal! 044|
wincmd w
argglobal
if bufexists(fnamemodify("include/gui/vectorInfoDialog.hpp", ":p")) | buffer include/gui/vectorInfoDialog.hpp | else | edit include/gui/vectorInfoDialog.hpp | endif
if &buftype ==# 'terminal'
  silent file include/gui/vectorInfoDialog.hpp
endif
balt include/gui/vectorInfoDialog.cpp
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
let s:l = 40 - ((7 * winheight(0) + 18) / 37)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 40
normal! 030|
wincmd w
exe 'vert 1resize ' . ((&columns * 132 + 95) / 190)
exe 'vert 2resize ' . ((&columns * 57 + 95) / 190)
tabnext
edit include/gui/vectorPickerDialog.cpp
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
exe 'vert 1resize ' . ((&columns * 95 + 95) / 190)
exe 'vert 2resize ' . ((&columns * 94 + 95) / 190)
argglobal
balt include/gui/vectorPickerDialog.hpp
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
let s:l = 119 - ((31 * winheight(0) + 18) / 37)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 119
normal! 026|
wincmd w
argglobal
if bufexists(fnamemodify("include/gui/vectorPickerDialog.hpp", ":p")) | buffer include/gui/vectorPickerDialog.hpp | else | edit include/gui/vectorPickerDialog.hpp | endif
if &buftype ==# 'terminal'
  silent file include/gui/vectorPickerDialog.hpp
endif
balt include/gui/vectorPickerDialog.cpp
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
let s:l = 51 - ((33 * winheight(0) + 18) / 37)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 51
normal! 0
wincmd w
exe 'vert 1resize ' . ((&columns * 95 + 95) / 190)
exe 'vert 2resize ' . ((&columns * 94 + 95) / 190)
tabnext
edit include/gui/vectorProcessorWidget.cpp
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
exe 'vert 1resize ' . ((&columns * 131 + 95) / 190)
exe 'vert 2resize ' . ((&columns * 58 + 95) / 190)
argglobal
balt include/gui/vectorProcessorWidget.hpp
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
let s:l = 300 - ((26 * winheight(0) + 18) / 37)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 300
normal! 0
wincmd w
argglobal
if bufexists(fnamemodify("include/gui/vectorProcessorWidget.hpp", ":p")) | buffer include/gui/vectorProcessorWidget.hpp | else | edit include/gui/vectorProcessorWidget.hpp | endif
if &buftype ==# 'terminal'
  silent file include/gui/vectorProcessorWidget.hpp
endif
balt include/gui/vectorProcessorWidget.cpp
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
let s:l = 83 - ((12 * winheight(0) + 18) / 37)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 83
normal! 0
wincmd w
exe 'vert 1resize ' . ((&columns * 131 + 95) / 190)
exe 'vert 2resize ' . ((&columns * 58 + 95) / 190)
tabnext
edit include/gui/vectorContainerWidget.cpp
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
exe 'vert 1resize ' . ((&columns * 121 + 95) / 190)
exe 'vert 2resize ' . ((&columns * 68 + 95) / 190)
argglobal
balt include/gui/vectorContainerWidget.hpp
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
let s:l = 27 - ((26 * winheight(0) + 18) / 36)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 27
normal! 047|
wincmd w
argglobal
if bufexists(fnamemodify("include/gui/vectorContainerWidget.hpp", ":p")) | buffer include/gui/vectorContainerWidget.hpp | else | edit include/gui/vectorContainerWidget.hpp | endif
if &buftype ==# 'terminal'
  silent file include/gui/vectorContainerWidget.hpp
endif
balt include/gui/vectorContainerWidget.cpp
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
let s:l = 26 - ((0 * winheight(0) + 18) / 36)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 26
normal! 0
wincmd w
exe 'vert 1resize ' . ((&columns * 121 + 95) / 190)
exe 'vert 2resize ' . ((&columns * 68 + 95) / 190)
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
exe 'vert 1resize ' . ((&columns * 118 + 95) / 190)
exe 'vert 2resize ' . ((&columns * 71 + 95) / 190)
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
let s:l = 61 - ((16 * winheight(0) + 18) / 37)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 61
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
let s:l = 21 - ((0 * winheight(0) + 18) / 37)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 21
normal! 0
wincmd w
exe 'vert 1resize ' . ((&columns * 118 + 95) / 190)
exe 'vert 2resize ' . ((&columns * 71 + 95) / 190)
tabnext
edit include/gui/guiTypes.hpp
argglobal
balt include/gui/vectorContainerWidget.hpp
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
let s:l = 1 - ((0 * winheight(0) + 18) / 37)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 1
normal! 0
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
exe 'vert 1resize ' . ((&columns * 92 + 95) / 190)
exe 'vert 2resize ' . ((&columns * 97 + 95) / 190)
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
let s:l = 664 - ((9 * winheight(0) + 18) / 37)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 664
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
let s:l = 102 - ((0 * winheight(0) + 18) / 37)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 102
normal! 0
wincmd w
exe 'vert 1resize ' . ((&columns * 92 + 95) / 190)
exe 'vert 2resize ' . ((&columns * 97 + 95) / 190)
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
exe 'vert 1resize ' . ((&columns * 103 + 95) / 190)
exe 'vert 2resize ' . ((&columns * 86 + 95) / 190)
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
let s:l = 39 - ((19 * winheight(0) + 18) / 37)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 39
normal! 067|
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
let s:l = 20 - ((0 * winheight(0) + 18) / 37)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 20
normal! 039|
wincmd w
exe 'vert 1resize ' . ((&columns * 103 + 95) / 190)
exe 'vert 2resize ' . ((&columns * 86 + 95) / 190)
tabnext
edit include/gui/transformationFormulaEditorDialog.cpp
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
exe 'vert 1resize ' . ((&columns * 78 + 95) / 190)
exe 'vert 2resize ' . ((&columns * 111 + 95) / 190)
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
let s:l = 86 - ((7 * winheight(0) + 18) / 37)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 86
normal! 051|
wincmd w
argglobal
if bufexists(fnamemodify("include/gui/transformationFormulaEditorDialog.hpp", ":p")) | buffer include/gui/transformationFormulaEditorDialog.hpp | else | edit include/gui/transformationFormulaEditorDialog.hpp | endif
if &buftype ==# 'terminal'
  silent file include/gui/transformationFormulaEditorDialog.hpp
endif
balt include/gui/transformationFormulaEditorDialog.cpp
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
let s:l = 46 - ((12 * winheight(0) + 18) / 37)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 46
normal! 049|
wincmd w
exe 'vert 1resize ' . ((&columns * 78 + 95) / 190)
exe 'vert 2resize ' . ((&columns * 111 + 95) / 190)
tabnext 5
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
