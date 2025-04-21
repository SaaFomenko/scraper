set tabstop=2
set softtabstop=2
set shiftwidth=2
set noexpandtab

set colorcolumn=80
highlight ColorColumn ctermbg=darkgray

augroup project
	autocmd!
	autocmd BufRead,BufNewFile *.h,*.c set filetype=c.doxygen
augroup END
