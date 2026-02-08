# MEDUSA – Development Diary

## 27-01-26  
Started programming **MEDUSA** today. The initial idea and project structure were clear. I planned a tool to **scan directories of code, analyze files, and generate AI-driven reports**. Everything seemed straightforward, and the project flow was well defined.

---

## 28-01-26  
Encountered my first major bug. I have a function that reads a file and stores all its content into a **pointer-to-pointer (`char **`)** structure. At first, it worked fine.  

The problem appeared during the **second loop**, when trying to overwrite the array of pointers that already had allocated memory from the first file. This caused a **Segmentation Fault (SegF)**.  

I considered creating a function to **remember the last allocated memory location** and append new content without overwriting. But I realized a simpler approach would work better: **open each file in a loop, append its content to a single aggregate file**, and then use that for the final report. This avoids manually managing memory for arrays of pointers and reduces the risk of segmentation faults.

I also ran into **directory path issues**—sometimes the code couldn’t locate the target files correctly. I had to carefully test paths and ensure the `read_dir()` function handled relative and absolute paths properly.

Despite these hurdles, I felt **excited about the Hackathon**. The process is as important as the result, and I’m learning a lot just debugging and iterating.

---

## 29-01-26  
Refined the **file aggregation workflow**:  
- The program now safely opens each file in the directory and writes its content to `out.txt`.  
- This makes generating the final AI report simple and prevents memory bugs from pointer mismanagement.  
- Tested with multiple directories and file counts to ensure stability.  

I also started integrating the **AI prompt construction** for Medusa, defining the **personality**: sarcastic, precise, critical, and educational.

---

## 30-01-26  
Decided on the **name MEDUSA**. A few reasons:  
1. **Personal inspiration** – in honor of a friend.  
2. **Symbolic meaning** – Medusa has snakes on her head, representing **multiple “eyes” or perspectives**, perfect for analyzing code from all angles.  
3. **Fits the AI personality** – critical, sharp, and capable of providing multiple layers of feedback in a single glance.

Also improved the **directory scanning** logic to handle nested directories and hidden files properly. Tested the tool to ensure **all readable code files are captured**.

---

## 31-01-26  
Polished the **report generation flow**:  
- AI prompt now includes all aggregated code and instructions for **detailed, sarcastic, and educational analysis**.  
- Multilingual support added (`pt` and `en`).  
- Verified that the **final report** (`relatorio.md`) is readable, clear, and captures the essence of MEDUSA’s critical personality.

---

## Lessons Learned & Reflections  

- **Memory management in C** is tricky; sometimes simpler solutions (like aggregating to a single file) avoid complex bugs.  
- **Directory paths** must be handled carefully, especially in cross-platform scenarios.  
- Building MEDUSA reinforced the importance of **planning workflow before coding**.  
- Naming and personality design matter: MEDUSA is not just a tool, it has **character**—which makes it more engaging for the Hackathon.  
- Excited to see how MEDUSA performs in real Hackathon conditions.  

---

This diary documents **the evolution of MEDUSA**, from first idea to functional tool with AI integration, debugging challenges, and the symbolic design decisions behind its name.