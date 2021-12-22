!cat:syntax:
!title:Syntax:
!sub:documentation:
!tag:syntax,documentation:
!start:
<p>
# Blush
Blush has it's own syntax, every command starts with ! at the start of the line and ends with : followed by the argument.
The first part is for tagging and categorization. Once the start command is given the indexing will stop.

## Blush indexing syntax

` !start: `, ends the indexing  
` !cat:[arg]:`, adds page to the category [arg]  
` !sub:[arg]:`, adds page to the sub category [arg]  
` !tag:[arg]:`, adds page to the tag [arg]  

## Blush document syntax

` !impcat:[arg]`, links every page that belongs to the sub category [arg] in a list  
` !imptag:[arg]`, links every page that belongs to the tag [arg] in a list  
` !impblog:[arg]:[n]`, creates a blog with the files in folder [arg] with [n] entries per page  
` !impimg:[arg]:[title]`, creates img element with the image [arg] and title [title]  

## Markdown

double space at the end of line creates a &#60;br&#62; tag.  
  
` \ `, escape character  
` # `, header, number of consecutive hashtags increases header level  
`` ` ``, begins codeblock, if multiple \` are used the code will have to be exited with that amount  
` *italic* `, makes italic appear as *italic*  
` __bold__ `, makes bold appear as __bold__  
` ~~strike~~ `, makes strike appear as ~~strike~~  
` __*bold italic*__ `, makes text  __*bold and italic*__  
</p>
