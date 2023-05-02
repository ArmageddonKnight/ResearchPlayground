
    // if (some_mysterious_ptr[3] != nullptr && some_mysterious_ptr[3] == ptr &&
    //     dmlc::GetEnv("VERBOSE_CACHING_ALLOCATOR", 0)) {
    //   LOG(INFO) << "Trying to free the allocated pointer";
    //   PyCodeObject* py_code_obj = nullptr;
    //   int py_frame_last_instr = 0;
    //   AllocationContext new_alloc_ctx(
    //       py_code_obj, py_frame_last_instr, 0, block->device);

    //   LOG(INFO) << "Over here now";

    //   if (true) {
    //     PyInterpreterState* py_main_interpreter_state =
    //         PyInterpreterState_Main();
    //     PyThreadState* py_thread_state =
    //         PyInterpreterState_ThreadHead(py_main_interpreter_state);

    //     LOG(INFO) << "Over here now";

    //     if (py_thread_state != nullptr && py_thread_state->frame != nullptr) {
    //       PyFrameObject* py_frame = py_thread_state->frame;

    //       LOG(INFO) << "Over here now";

    //       if (py_frame != nullptr) {
    //         py_code_obj = py_frame->f_code;
    //         py_frame_last_instr = py_frame->f_lasti;
    //         LOG(INFO) << "Over here now";
    //       }

    //       LOG(INFO) << "Over here now";

    //       while (py_frame != nullptr) {
    //         // int line = frame->f_lineno;
    //         /*
    //          frame->f_lineno will not always return the correct line number
    //          you need to call PyCode_Addr2Line().
    //         */
    //         int line = PyCode_Addr2Line(py_frame->f_code, py_frame->f_lasti);
    //         const char* filename =
    //             PyUnicode_AsUTF8(py_frame->f_code->co_filename);
    //         const char* funcname = PyUnicode_AsUTF8(py_frame->f_code->co_name);
    //         LOG(INFO) << "    " << filename << "(" << line << "): " << funcname;
    //         py_frame = py_frame->f_back;
    //       }
    //     } // if (py_thread_state != nullptr && py_thread_state->frame !=
    //       // nullptr)
    //   }
    //   // // LOG(FATAL) << "Trying to free the allocated pointer";
    //   LOG(INFO) << "Over here now";
    //   new_alloc_ctx.f_code = py_code_obj;
    //   new_alloc_ctx.f_lasti = py_frame_last_instr;
    //   LOG(INFO) << "Over here now";

    //   // if (dmlc::GetEnv("VERBOSE_CACHING_ALLOCATOR", 0)) {
    //   LOG(INFO) << "Pointer free checkpoint="
    //             << dmlc::GetEnv("POINTER_FREE_CHECKPOINT", std::string(""));
    //   if (new_alloc_ctx.f_code != nullptr) {
    //     LOG(INFO) << new_alloc_ctx;
    //   } else {
    //   }
    //   LOG(FATAL) << "My love~" << dmlc::StackTrace(1, 25);
    //   // }
    // }


    // PyCodeObject* py_code_obj = nullptr;
    // int py_frame_last_instr = 0;
    // AllocationContext new_alloc_ctx(
    //     py_code_obj, py_frame_last_instr, s_alloc_ctx_contig_cnt, device);

    // if (true) {
    //   PyInterpreterState* py_main_interpreter_state = PyInterpreterState_Main();
    //   PyThreadState* py_thread_state =
    //       PyInterpreterState_ThreadHead(py_main_interpreter_state);
    //   if (py_thread_state != nullptr && py_thread_state->frame != nullptr) {
    //     PyFrameObject* py_frame = py_thread_state->frame;

    //     if (py_frame != nullptr) {
    //       py_code_obj = py_frame->f_code;
    //       py_frame_last_instr = py_frame->f_lasti;
    //     }
    //   } // if (py_thread_state != nullptr && py_thread_state->frame != nullptr)
    // }
    // new_alloc_ctx.f_code = py_code_obj;
    // new_alloc_ctx.f_lasti = py_frame_last_instr;
    // if (dmlc::GetEnv("VERBOSE_CACHING_ALLOCATOR", 0)) {
    //   LOG(INFO) << new_alloc_ctx;
    // }

    //     if (!taping_malloc && !using_taped_malloc) {
    //   for (auto& tape : taped_alloc_params_with_block_copy) {
    //     for (auto& kv : tape.second) {
    //       if (kv.second.ptr == block->ptr) {
    //         LOG(WARNING) << "Trying to free block->ptr=" << (&kv.second)
    //                      << " from " << tape.first;
    //       }
    //     }
    //   }
    // }