# Stanford CS149 Parallel Computing - Development Environment Setup

This README provides setup instructions for tools needed for running Stanford CS149 (Parallel Computing) assignments on an Azure D4s_v3 virtual machine.

---

## Azure VM Specifications


**Compute Resources:**
- **vCPUs**: 4 virtual CPUs
- **Physical Cores**: 2 physical cores
- **Hyper-Threading**: Enabled (2 threads per physical core)
  - Each physical core supports 2 simultaneous hardware threads
  - Total of 4 logical processors (2 cores × 2 threads/core)
- **Processor**: Intel(R) Xeon(R) Platinum 8272CL CPU @ 2.60GHz
- **Architecture**: x86-64 with AVX, SSE, SSE2, AVX2, SSE3, SSE4, AVX512 and AVX512 VNNI support

**Memory:**
- **RAM**: 16 GB
- **Memory-to-vCPU Ratio**: 4 GB per vCPU

**Storage:**
- **Temporary (Local SSD)**: 32 GB
  - High-performance SSD-based temporary storage
  - Note: Data is not persistent across VM deallocations
- **OS Disk**: Variable (typically 30+ GB, configurable)
- **Premium Storage**: Supported (for additional data disks)

---

## Miniconda Installation

Miniconda provides a minimal Python distribution with the conda package manager, ideal for managing Python environments on Linux systems.

### Download Miniconda

```bash
# Download the latest Miniconda installer for Linux (x86_64)
wget https://repo.anaconda.com/miniconda/Miniconda3-latest-Linux-x86_64.sh

# Alternative: use curl if wget is not available
curl -O https://repo.anaconda.com/miniconda/Miniconda3-latest-Linux-x86_64.sh
```

### Install Miniconda

```bash
# Make the installer executable
chmod +x Miniconda3-latest-Linux-x86_64.sh

# Run the installer
bash Miniconda3-latest-Linux-x86_64.sh

# Follow the prompts:
# - Press ENTER to review the license
# - Type 'yes' to accept the license terms
# - Press ENTER to confirm the installation location (default: ~/miniconda3)
# - Type 'yes' to initialize Miniconda in your shell
```

### Activate Miniconda

```bash
# Close and reopen your terminal, or run:
source ~/.bashrc

# Verify installation
conda --version
python --version
```

### Configure Conda (Optional but Recommended)

```bash
# Disable automatic base environment activation (optional)
conda config --set auto_activate_base false

# Create a new environment for CS149
conda create -n cs149 python=3.11 -y

# Activate the environment
conda activate cs149
```

---

**ISPC (Intel SPMD Program Compiler)**

ISPC is required for Assignment 1's SIMD programming exercises.

```bash
# Download ISPC (v1.24.0 or later)
cd ~/Downloads
wget https://github.com/ispc/ispc/releases/download/v1.28.1/ispc-v1.28.1-linux.tar.gz

# Extract
tar -xzf ispc-v1.28.1-linux.tar.gz

# Add to PATH (add this to ~/.bashrc for persistence)
export PATH=$PATH:${HOME}/Downloads/ispc-v1.28.1-linux/bin

# Verify installation
ispc --version
```