# MEDUSA

**MEDUSA** is an **open-source** automated code analysis tool, designed for **hackathons**, combining **native C** and **Gemini AI** to generate **critical, sarcastic, and highly detailed reports** on source code.

---

## 🎯 Objective

- Automate directory-wide code analysis  
- Detect errors, assess severity, and programmer level  
- Provide **strategic, sarcastic, and educational feedback**  
- Showcase **advanced integration of C with AI**  

---

## ⚡ Why C?

- **Optimization**: full control over memory and performance  
- **Portability**: runs on any minimal environment with `libc`  
- **Efficient code**: for programmers who value performance and clean design  

---

## 🛠 Main Features

- **Directory and file scanning**  
  - Ignores hidden files  
  - Aggregates code in memory for analysis  

- **Report generation via Gemini API**  
  - Prompt built with Medusa's personality: sarcastic and precise  
  - JSON response converted into **clean, readable report**  

- **Multilingual**: supports Portuguese (`pt`) or English (`en`)  

- **Configurable**:  
  - Maximum number of files and lines per file  
  - Report buffer size  

- **Secure and Open-source**:  
  - API key is never exposed  
  - Compiled binary is ready-to-run and secure  

---

## 🔄 Technical Flow

```
+-------------------+
| Code Directory    |
+-------------------+
          |
          v
+-------------------+
| run() Function    |
| Reads files and   |
| aggregates in    |
| out.txt           |
+-------------------+
          |
          v
+-------------------+
| Prompt Construction|
| for Gemini AI      |
| (Medusa Personality)|
+-------------------+
          |
          v
+-------------------+
| Send to Gemini AI |
+-------------------+
          |
          v
+-------------------+
| Extract JSON to   |
| clean text        |
+-------------------+
          |
          v
+-------------------+
| Final Report      |
| relatorio.md      |
+-------------------+
```

---

## 🏃‍♂️ How to Run

```bash
# Compile with Makefile
make

# Run analysis
./medusa run ./my_project en
```

- `./my_project` → directory containing the code to analyze  
- `en` → generates report in English (`pt` for Portuguese)  

The binary handles the **entire workflow automatically**: reading files, sending to AI, and generating the final report.

---

## ⚙️ Customization

- Adjust **BUFFER_SIZE**, maximum number of files, and lines per file as needed  
- Works for small or large projects  
- Generates detailed reports even for directories with many files  

---

## 🏆 Value for Hackathon Judges

- **Innovation**: native C + Gemini AI, a rare combination for hackathons  
- **Immediate execution**: ready-to-run binary, zero configuration  
- **Clarity**: critical, sarcastic report, easy to read  
- **Flexible and audit-friendly**: open-source, adjustable, and secure  
- **Visual impact**: clear workflow and strategic report, easy to present in a pitch  

---

**MEDUSA** turns any code directory into a **strategic, educational, and entertaining report**, demonstrating technical mastery, optimization, and advanced AI integration.