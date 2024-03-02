from pypdf import PdfReader
from pathlib import Path

counter = 1

for p in Path('E:/COSC 4315 (Info and Knowledge Management)/PDF Reader/Research Papers').glob('*.pdf'):
    pdf_reader = PdfReader(p)

    page_content = {}


    output = open("Document " + str(counter) + ".txt", "w")

   
    for indx, pdf_page in enumerate(pdf_reader.pages):
        if indx > 1:
            break
        page_content[indx + 1] = pdf_page.extract_text()
        page_text = page_content[indx + 1]
        print(page_text.encode(encoding = 'UTF-8', errors = 'strict'), file=output)
        


    counter += 1

