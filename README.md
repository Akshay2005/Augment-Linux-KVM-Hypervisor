# Augment-Linux-KVM-Hypervisor
Developed a modified linux kernel with an augmented KVM to allow with additional hypercalls to be used as new functionality.

## Instruction 1 – NEWCPUID
- The NEWCPUID feature is encoded as the hypercall number 0F 3B, encoded in the low 32 bits of %RAX. The high 32 bits of %RAX represent the input %EAX to a regular CPUID instruction. It otherwise behaves identically to the x86 CPUID instruction.

## Instruction 2 – NEWCPUID2
- The NEWCPUID2 instruction opcode is encoded as the hypercall number 0F 3C, encoded in the low 32 bits of %RAX. It otherwise behaves identically to the NEWCPUID instruction, with the following addition:
  1. NEWCPUID2 leaf node 0xA0000000 returns the following information:
  2. EAX = ‘EPMC’   (encoded as bytes) ◦ EBX = ‘\0382’     (encoded as bytes, \0 == null byte) ◦ All other registers unchanged
  
## Instruction 3 – GETCTR
- The GETCTR instruction opcode is encoded as the hypercall number 0F 3D, as encoded in the low 32 bits of %RAX. It is used to return a counter value that increments by one each time it is called. The GETCTR instruction can be called at any CPL, and behaves as follows:
  - EAX = counter value
  - counter_value++
  - All other registers unchanged
